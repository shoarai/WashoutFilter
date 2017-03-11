// Copyright (c) 2017 shoarai

#include "WashoutFilter.h"
#include "typedef.h"

#include <iostream> // memset用
#include <math.h>

WashoutFilter::WashoutFilter(Filter *TranslationHighPassFilter[3],
                             Filter *TranslationLowPassFilter[2],
                             Filter *RotationHighPassFilter[3],
                             unsigned int interval_ms)
    : interval_ms(interval_ms), GRAVITY_mm(9.80665 * 1000), m_x(), m_y(), m_z(),
      m_phi(), m_sit(), m_psi(), m_vx(), m_vy(), m_vz(), phi_t(), phi_r(),
      sit_t(), sit_r(), gravityX(), gravityY(), gravityZ(), transScale(1),
      rotateScale(1) {
  memset(&stPilot, 0, sizeof(stPilot));

  tHPFs[0] = TranslationHighPassFilter[0];
  tHPFs[1] = TranslationHighPassFilter[1];
  tHPFs[2] = TranslationHighPassFilter[2];

  rLPFs[0] = TranslationLowPassFilter[0];
  rLPFs[1] = TranslationLowPassFilter[1];

  rHPFs[0] = RotationHighPassFilter[0];
  rHPFs[1] = RotationHighPassFilter[1];
  rHPFs[2] = RotationHighPassFilter[2];
}

WashoutFilter::~WashoutFilter() {
  // TODO:
  // delete[] tHPF[3];
  // delete[] rLPF[3];
  // delete[] rHPF[3];
}

// 機能		：ウォッシュアウト処理
// 引数		：航空機の並進加速度と角速度
Position WashoutFilter::doFilter(Motion &motion) {
  //------------------------------------------//
  // Translation //
  //------------------------------------------//
  // フィルタスケール
  double ax_scale = motion.getAccelerationX() * transScale;
  double ay_scale = motion.getAccelerationY() * transScale;
  double az_scale = motion.getAccelerationZ() * transScale;

  // 重力加速度を加える
  double ax_g = ax_scale + gravityX;
  double ay_g = ay_scale + gravityY;
  double az_g = az_scale + gravityZ - GRAVITY_mm;

  // 並進加速度をハイパスフィルタ処理する
  double ax_hp = tHPFs[0]->doFilter(ax_g);
  double ay_hp = tHPFs[1]->doFilter(ay_g);
  double az_hp = tHPFs[2]->doFilter(az_g);

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
  double ax_lp = rLPFs[0]->doFilter(ax_scale);
  double ay_lp = rLPFs[1]->doFilter(ay_scale);

  // 持続加速度を傾斜角に変換する
  sit_t = -asin(ax_lp / GRAVITY_mm);
  phi_t = asin(ay_lp / GRAVITY_mm);

  // asinのエラー検知（）
  if (!(-deg2rad(90) <= sit_t && sit_t <= deg2rad(90))) {
    if (ax_lp < 0) {
      sit_t = deg2rad(90);
    } else {
      sit_t = -deg2rad(90);
    }
  }
  if (!(-deg2rad(90) <= phi_t && phi_t <= deg2rad(90))) {
    if (ay_lp > 0) {
      phi_t = deg2rad(90);
    } else {
      phi_t = -deg2rad(90);
    }
  }

  //------------------------------------------//
  // Rotation //
  //------------------------------------------//
  // フィルタスケール
  double vphi_scale = motion.getAngularVelocityX() * rotateScale;
  double vsit_scale = motion.getAngularVelocityY() * rotateScale;
  double vpsi_scale = motion.getAngularVelocityZ() * rotateScale;

  // 角速度をハイパスフィルタ処理する
  double wphi_hp = rHPFs[0]->doFilter(vphi_scale);
  double wsit_hp = rHPFs[1]->doFilter(vsit_scale);
  double wpsi_hp = rHPFs[2]->doFilter(vpsi_scale);

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
  double sphi = sin(m_phi);
  double cphi = cos(m_phi);
  double ssit = sin(m_sit);
  double csit = cos(m_sit);

  // 重力加速度gs
  gravityX = GRAVITY_mm * (-ssit);
  gravityY = GRAVITY_mm * sphi * csit;
  gravityZ = GRAVITY_mm * cphi * csit;

  // パイロットの体感加速度の算出
  stPilot.ax = ax_hp + ax_lp;
  stPilot.ay = ay_hp + ay_lp;
  stPilot.az = az_hp;
  stPilot.wphi = wphi_hp;
  stPilot.wsit = wsit_hp;
  stPilot.wpsi = wpsi_hp;

  // ψの回転だけ適用
  sphi = sin(0.0);
  cphi = cos(0.0);
  ssit = sin(0.0);
  csit = cos(0.0);
  double spsi = sin(m_psi);
  double cpsi = cos(m_psi);

  // 回転行列
  double matT[3][3] = {
      {csit * cpsi, csit * spsi, -ssit},
      {sphi * ssit * cpsi - cphi * spsi, sphi * ssit * spsi + cphi * cpsi,
       sphi * csit},
      {cphi * ssit * cpsi - sphi * spsi, cphi * ssit * spsi - sphi * cpsi,
       cphi * csit},
  };

  double pi_ax = stPilot.ax * matT[0][0] + stPilot.ay * matT[1][0] +
                 stPilot.az * matT[2][0];
  double pi_ay = stPilot.ax * matT[0][1] + stPilot.ay * matT[1][1] +
                 stPilot.az * matT[2][1];
  double pi_az = stPilot.ax * matT[0][2] + stPilot.ay * matT[1][2] +
                 stPilot.az * matT[2][2];

  stPilot.ax = pi_ax;
  stPilot.ay = pi_ay;
  stPilot.az = pi_az;

  Position position(m_x, m_y, m_z, m_phi, m_sit, m_psi);
  return position;
}

void WashoutFilter::setTranslationScale(const double &scale) {
  transScale = scale;
}
void WashoutFilter::setRotationScale(const double &scale) {
  rotateScale = scale;
}
