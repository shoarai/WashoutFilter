#include "Position.h"

class Filter;

class WashoutFilter {
public:
  WashoutFilter(unsigned int t_ms);
  ~WashoutFilter();

  Position doFilter(const double &, const double &, const double &,
                    const double &, const double &, const double &);
  void setTranslationScale(const double &scale);
  void setRotationScale(const double &scale);

private:
  Filter *tHPF[3];
  Filter *rLPF[3];
  Filter *rHPF[3];

  unsigned int interval_ms; // 計算周期
  double transScale;        // 並進のスケール
  double rotateScale;       // 回転のスケール

  // 重力加速度gs
  double gravityX;
  double gravityY;
  double gravityZ;
  const double GRAVITY_mm; // �d�͉����x[mm/s2]

  // 中間媒介変数、速度、角度
  double m_vx, m_vy, m_vz, phi_t, phi_r, sit_t, sit_r;
  double m_x, m_y, m_z, m_phi, m_sit, m_psi;

  // パイロットの体感運動
  struct st6DOF {
    double ax, ay, az, wphi, wsit, wpsi;
  } stPilot;

  // 積分
  inline double timeInteg(const double &x, const double &v) {
    return (x + v * interval_ms / 1000);
  }
};
