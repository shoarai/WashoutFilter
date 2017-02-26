#include "../src/MotionFilter.h"

// Translationのハイパスフィルタ
class JAXA_tHPF : public MotionFilter {
public:
  explicit JAXA_tHPF(unsigned int t_ms, const double &cutoff)
      : MotionFilter(t_ms, cutoff){};
  double doFilter(const double &);
};

// Tilt-Coordinationのローパスフィルタ
class JAXA_tLPF : public MotionFilter {
private:
  // ダンピング係数
  double damp;

public:
  explicit JAXA_tLPF(unsigned int t_ms, const double &cutoff, const double &dmp)
      : MotionFilter(t_ms, cutoff), damp(dmp){};
  double doFilter(const double &);
};

// Rotationのハイパスフィルタ
class JAXA_rHPF : public MotionFilter {
public:
  explicit JAXA_rHPF(unsigned int t_ms, const double &cutoff)
      : MotionFilter(t_ms, cutoff){};
  double doFilter(const double &);
};
