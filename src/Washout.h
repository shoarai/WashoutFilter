// #include "../../arith/src/Vector.h"

class Filter;

class Washout{
private:
	unsigned int time_ms;		// 計算周期
	double transScale;	// 並進のスケール
	double rotateScale;	// 回転のスケール

	// 重力加速度gs
	// arith::Vector vecGs;
	double gravityX;
	double gravityY;
	double gravityZ;
	const double GRAVITY_mm;	// �d�͉����x[mm/s2]

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
	inline double timeInteg(const double& x, const double& v){
		return (x + v * time_ms / 1000);
	}

public:
	Washout(unsigned int t_ms, const double& tScale = 1, const double& rScale = 1);
	~Washout();

	// ウォッシュアウト処理
	void washout(const double&, const double&, const double&, const double&, const double&, const double& );

	// 変数取得
	const double getx()	  const{ return m_x; };
	const double gety()	  const{ return m_y; };
	const double getz()	  const{ return m_z; };
	const double getPhi() const{ return m_phi; };
	const double getSit() const{ return m_sit; };
	const double getPsi() const{ return m_psi; };
};
