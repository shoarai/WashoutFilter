#pragma once

#include "..¥Vector¥Vector.h"

class Filter;

class Washout{
private:
	UINT   time_ms;		// 計算周期
	double transScale;	// 並進のスケール
	double rotateScale;	// 回転のスケール

	// 重力加速度gs
	Vector vecGs;

	// 出力値
	double m_x, m_y, m_z, m_phi, m_sit, m_psi;

	// 中間媒介変数、速度、角度
	double m_vx, m_vy, m_vz, phi_t, phi_r, sit_t, sit_r;

	// パイロットの体感運動
	struct st6DOF{
		double ax, ay, az, wphi, wsit, wpsi;
	}stPilot;

	//------------------------------------------//
	// フィルタ									//
	//------------------------------------------//
	Filter* tHPF[3];
	Filter* rLPF[3];
	Filter* rHPF[3];

	//------------------------------------------//
	// インライン								//
	//------------------------------------------//
	// 積分
	inline double timeInteg(CDBL& x, CDBL& v){
		return (x + v * msec2sec(time_ms));
	}

public:
	Washout(UINT t_ms, CDBL& tScale = 1, CDBL& rScale = 1);
	~Washout();

	// ウォッシュアウト処理
	void washout(CDBL&, CDBL&, CDBL&, CDBL&, CDBL&, CDBL& );

	// 変数取得
	CDBL getx()	  const{ return m_x; };
	CDBL gety()	  const{ return m_y; };
	CDBL getz()	  const{ return m_z; };
	CDBL getPhi() const{ return m_phi; };
	CDBL getSit() const{ return m_sit; };
	CDBL getPsi() const{ return m_psi; };
};
