#include "Washout.h"
#include "Filter.h"

#include <iostream>	// memset用

Washout::Washout(UINT t_ms, CDBL& tScale, CDBL& rScale) :
	time_ms(t_ms),
	transScale(tScale),
	rotateScale(rScale),
	vecGs(0, 0, GRAVITY_mm)
{
	// 初期化
	m_x = m_y = m_z = m_phi = m_sit = m_psi = 0;
	m_vx = m_vy = m_vz = phi_t = phi_r = sit_t = sit_r = 0;

	memset( &stPilot, 0, sizeof(stPilot) );

	// フィルタ変数
	double freq_wn  = 2.5;			// ωn ：折れ点周波数（ハイパス）
	double freq_wlp = 2 * freq_wn;	// ωLP：折れ点周波数（ローパス）
	double damp		= 1;			// ζLP：ダンピング係数

	// Translationのハイパスフィルタ
	tHPF[0] = new JAXA_tHPF(time_ms, freq_wn);
	tHPF[1] = new JAXA_tHPF(time_ms, freq_wn);
	tHPF[2] = new JAXA_tHPF(time_ms, freq_wn);

	// Tilt-Coordinationのローパスフィルタ
	rLPF[0] = new JAXA_tLPF(time_ms, freq_wlp, damp);
	rLPF[1] = new JAXA_tLPF(time_ms, freq_wlp, damp);
	rLPF[2] = new JAXA_tLPF(time_ms, freq_wlp, damp);

	// Rotationのハイパスフィルタ
	rHPF[0] = new JAXA_rHPF(time_ms, freq_wn);
	rHPF[1] = new JAXA_rHPF(time_ms, freq_wn);
	rHPF[2] = new JAXA_rHPF(time_ms, freq_wn);
}

Washout::~Washout()
{
	delete[] tHPF[3];
	delete[] rLPF[3];
	delete[] rHPF[3];
}

// 機能		：ウォッシュアウト処理
// 引数		：航空機の並進加速度と角速度
void Washout::washout( CDBL& ax, CDBL& ay, CDBL& az, CDBL& wphi, CDBL& wsit, CDBL& wpsi )
{
	//------------------------------------------//
	// Translation								//
	//------------------------------------------//
	// フィルタスケール
	double ax_scale = ax * transScale;
	double ay_scale = ay * transScale;
	double az_scale = az * transScale;

	// 重力加速度を加える
	double ax_g = ax_scale + vecGs.getx();
	double ay_g = ay_scale + vecGs.gety();
	double az_g = az_scale + vecGs.getz() - GRAVITY_mm;

	// 並進加速度をハイパスフィルタ処理する
	double ax_hp = tHPF[0]->filtering( ax_g );
	double ay_hp = tHPF[1]->filtering( ay_g );
	double az_hp = tHPF[2]->filtering( az_g );

	// 速度算出
	m_vx = timeInteg(m_vx, ax_hp);
	m_vy = timeInteg(m_vy, ay_hp);
	m_vz = timeInteg(m_vz, az_hp);

	// 変位算出
	m_x = timeInteg(m_x, m_vx);
	m_y = timeInteg(m_y, m_vy);
	m_z = timeInteg(m_z, m_vz);

	//------------------------------------------//
	// Tilt-coordination						//
	//------------------------------------------//
	// ローパスフィルタ処理
	double ax_lp = rLPF[0]->filtering( ax_scale );
	double ay_lp = rLPF[1]->filtering( ay_scale );

	// 持続加速度を傾斜角に変換する
	sit_t = - asin( ax_lp / GRAVITY_mm );
	phi_t =   asin( ay_lp / GRAVITY_mm );

	// asinのエラー検知（）
	if( !(-deg2rad(90) <= sit_t && sit_t <= deg2rad(90)) ){
		if(ax_lp < 0){
			sit_t = deg2rad(90);
		}else{
			sit_t = -deg2rad(90);
		}
	}
	if( !(-deg2rad(90) <= phi_t && phi_t <= deg2rad(90)) ){
		if(ay_lp > 0){
			phi_t = deg2rad(90);
		}else{
			phi_t = -deg2rad(90);
		}
	}

	//------------------------------------------//
	// Rotation									//
	//------------------------------------------//
	// フィルタスケール
	double vphi_scale = wphi * rotateScale;
	double vsit_scale = wsit * rotateScale;
	double vpsi_scale = wpsi * rotateScale;

	// 角速度をハイパスフィルタ処理する
	double wphi_hp = rHPF[0]->filtering( vphi_scale );
	double wsit_hp = rHPF[1]->filtering( vsit_scale );
	double wpsi_hp = rHPF[2]->filtering( vpsi_scale );

	// 回転運動の角度を算出する
	phi_r = timeInteg(phi_r, wphi_hp);
	sit_r = timeInteg(sit_r, wsit_hp);
	m_psi = timeInteg(m_psi, wpsi_hp);


	//------------------------------------------//
	// Tilt角 ＋ Rotation角						//
	//------------------------------------------//
	// Tilt-coordinationとRotationの角度を加算する
	m_phi = phi_t + phi_r;
	m_sit = sit_t + sit_r;

	//------------------------------------------//
	// 重力加速度gsの算出						//
	//------------------------------------------//
	// 回転行列の成分
	double sphi = sin( m_phi );
	double cphi = cos( m_phi );
	double ssit = sin( m_sit );
	double csit = cos( m_sit );

	// 重力加速度gs
	vecGs.set(
		GRAVITY_mm *   (-ssit),
		GRAVITY_mm * sphi * csit,
		GRAVITY_mm * cphi * csit );

	//------------------------------------------//
	// パイロットの体感加速度の算出				//
	//------------------------------------------//
	stPilot.ax   = ax_hp + ax_lp;
	stPilot.ay   = ay_hp + ay_lp;
	stPilot.az   = az_hp;
	stPilot.wphi = wphi_hp;
	stPilot.wsit = wsit_hp;
	stPilot.wpsi = wpsi_hp;

	// ψの回転だけ適用
	sphi = sin( 0.0 );
	cphi = cos( 0.0 );
	ssit = sin( 0.0 );
	csit = cos( 0.0 );
	double spsi = sin( m_psi );
	double cpsi = cos( m_psi );

	// 回転行列
	double matT[3][3] = {
		{			csit * cpsi			 ,			csit * spsi			   ,	-ssit	},
		{sphi * ssit * cpsi - cphi * spsi, sphi * ssit * spsi + cphi * cpsi, sphi * csit},
		{cphi * ssit * cpsi - sphi * spsi, cphi * ssit * spsi - sphi * cpsi, cphi * csit},
	};

	double pi_ax = stPilot.ax * matT[0][0] + stPilot.ay * matT[1][0] + stPilot.az * matT[2][0];
	double pi_ay = stPilot.ax * matT[0][1] + stPilot.ay * matT[1][1] + stPilot.az * matT[2][1];
	double pi_az = stPilot.ax * matT[0][2] + stPilot.ay * matT[1][2] + stPilot.az * matT[2][2];

	stPilot.ax = pi_ax;
	stPilot.ay = pi_ay;
	stPilot.az = pi_az;

	return;
}
