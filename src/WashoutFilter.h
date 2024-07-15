// Copyright (c) 2017 shoarai

#include <array>
#include <memory>

#include "IWashoutFilter.h"

#include "IFilter.h"

namespace WashoutFilter
{
class WashoutFilter : public IWashoutFilter
{
public:
	WashoutFilter(const std::array<std::shared_ptr<IFilter>, 3>& TranslationHighPassFilter,
	              const std::array<std::shared_ptr<IFilter>, 2>& TranslationLowPassFilter,
	              const std::array<std::shared_ptr<IFilter>, 3>& RotationHighPassFilter,
	              unsigned int t_ms);
  ~WashoutFilter();

  Position doFilter(Motion &motion);
  void setTranslationScale(const double &scale);
  void setRotationScale(const double &scale);

private:
	std::array<std::shared_ptr<IFilter>, 3> tHPFs;
	std::array<std::shared_ptr<IFilter>, 2> rLPFs;
	std::array<std::shared_ptr<IFilter>, 3> rHPFs;

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

  inline double integrateWithTime(const double &x, const double &v)
  {
    return (x + (v * interval_ms / 1000));
  }
};
}
