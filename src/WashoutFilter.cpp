// Copyright (c) 2017 shoarai

#include "WashoutFilter.h"
#include "typedef.h"

#include <iostream> // for memset
#include <math.h>

WashoutFilter::WashoutFilter(
    IFilter *TranslationHighPassFilter[3],
    IFilter *TranslationLowPassFilter[2],
    IFilter *RotationHighPassFilter[3],
    unsigned int interval_ms)
    : interval_ms(interval_ms), GRAVITY_mm(9.80665 * 1000), m_x(), m_y(), m_z(),
      m_phi(), m_sit(), m_psi(), m_vx(), m_vy(), m_vz(),
      phi_t(), phi_r(), sit_t(), sit_r(),
      gravityX(), gravityY(), gravityZ(),
      transScale(1), rotateScale(1)
{
  tHPFs[0] = TranslationHighPassFilter[0];
  tHPFs[1] = TranslationHighPassFilter[1];
  tHPFs[2] = TranslationHighPassFilter[2];

  rLPFs[0] = TranslationLowPassFilter[0];
  rLPFs[1] = TranslationLowPassFilter[1];

  rHPFs[0] = RotationHighPassFilter[0];
  rHPFs[1] = RotationHighPassFilter[1];
  rHPFs[2] = RotationHighPassFilter[2];
}

WashoutFilter::~WashoutFilter()
{
  // TODO:
  // delete[] tHPF[3];
  // delete[] rLPF[3];
  // delete[] rHPF[3];
}

Position WashoutFilter::doFilter(Motion &motion)
{
  //------------------------------------------//
  // Translation
  //------------------------------------------//
  double ax_scale = motion.getAccelerationX() * transScale;
  double ay_scale = motion.getAccelerationY() * transScale;
  double az_scale = motion.getAccelerationZ() * transScale;

  double ax_g = ax_scale + gravityX;
  double ay_g = ay_scale + gravityY;
  double az_g = az_scale + gravityZ - GRAVITY_mm;

  double ax_hp = tHPFs[0]->doFilter(ax_g);
  double ay_hp = tHPFs[1]->doFilter(ay_g);
  double az_hp = tHPFs[2]->doFilter(az_g);

  m_vx = timeInteg(m_vx, ax_hp);
  m_vy = timeInteg(m_vy, ay_hp);
  m_vz = timeInteg(m_vz, az_hp);

  m_x = timeInteg(m_x, m_vx);
  m_y = timeInteg(m_y, m_vy);
  m_z = timeInteg(m_z, m_vz);

  //------------------------------------------//
  // Tilt-coordination
  //------------------------------------------//
  double ax_lp = rLPFs[0]->doFilter(ax_scale);
  double ay_lp = rLPFs[1]->doFilter(ay_scale);

  // Convert low pass acceraration to tilt angle
  sit_t = -asin(ax_lp / GRAVITY_mm);
  phi_t = asin(ay_lp / GRAVITY_mm);

  // Check asin error
  if (!(-deg2rad(90) <= sit_t && sit_t <= deg2rad(90)))
  {
    if (ax_lp < 0)
    {
      sit_t = deg2rad(90);
    }
    else
    {
      sit_t = -deg2rad(90);
    }
  }
  if (!(-deg2rad(90) <= phi_t && phi_t <= deg2rad(90)))
  {
    if (ay_lp > 0)
    {
      phi_t = deg2rad(90);
    }
    else
    {
      phi_t = -deg2rad(90);
    }
  }

  //------------------------------------------//
  // Rotation
  //------------------------------------------//
  double vphi_scale = motion.getAngularVelocityX() * rotateScale;
  double vsit_scale = motion.getAngularVelocityY() * rotateScale;
  double vpsi_scale = motion.getAngularVelocityZ() * rotateScale;

  double wphi_hp = rHPFs[0]->doFilter(vphi_scale);
  double wsit_hp = rHPFs[1]->doFilter(vsit_scale);
  double wpsi_hp = rHPFs[2]->doFilter(vpsi_scale);

  phi_r = timeInteg(phi_r, wphi_hp);
  sit_r = timeInteg(sit_r, wsit_hp);
  m_psi = timeInteg(m_psi, wpsi_hp);

  //------------------------------------------//
  // Tilt ＋ Rotation
  //------------------------------------------//
  m_phi = phi_t + phi_r;
  m_sit = sit_t + sit_r;

  //------------------------------------------//
  // Calculate gs
  //------------------------------------------//
  double sphi = sin(m_phi);
  double cphi = cos(m_phi);
  double ssit = sin(m_sit);
  double csit = cos(m_sit);
  gravityX = GRAVITY_mm * (-ssit);
  gravityY = GRAVITY_mm * sphi * csit;
  gravityZ = GRAVITY_mm * cphi * csit;

  Position position(m_x, m_y, m_z, m_phi, m_sit, m_psi);
  return position;
}

void WashoutFilter::setTranslationScale(const double &scale)
{
  transScale = scale;
}

void WashoutFilter::setRotationScale(const double &scale)
{
  rotateScale = scale;
}
