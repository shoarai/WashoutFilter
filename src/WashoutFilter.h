// Copyright (c) 2017 shoarai

#include "IWashoutFilter.h"

#include "IFilter.h"

class WashoutFilter : public IWashoutFilter
{
public:
  WashoutFilter(IFilter *TranslationHighPassFilter[3],
                IFilter *TranslationLowPassFilter[2],
                IFilter *RotationHighPassFilter[3], unsigned int t_ms);
  ~WashoutFilter();

  Position doFilter(Motion &motion);
  void setTranslationScale(const double &scale);
  void setRotationScale(const double &scale);

private:
  IFilter *tHPFs[3];
  IFilter *rLPFs[2];
  IFilter *rHPFs[3];

  const double GRAVITY_mm; // [mm/s2]
  double gravityX;
  double gravityY;
  double gravityZ;

  // Intermediate parameters velocities and angles
  double m_vx, m_vy, m_vz, phi_t, phi_r, sit_t, sit_r;
  double m_x, m_y, m_z, m_phi, m_sit, m_psi;

  unsigned int interval_ms; // Sampling interval[ms]
  double transScale;        // Scale for translation
  double rotateScale;       // Scale for rotation

  struct st6DOF
  {
    double ax, ay, az, wphi, wsit, wpsi;
  } stPilot;

  inline double timeInteg(const double &x, const double &v)
  {
    return (x + (v * interval_ms / 1000));
  }
};
