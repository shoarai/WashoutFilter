// Copyright (c) 2017 shoarai

#include "../src/MotionFilter.h"

// Translationのハイパスフィルタ
class Sample_tHPF : public MotionFilter {
public:
  explicit Sample_tHPF(unsigned int t_ms, const double &cutoff)
      : MotionFilter(t_ms, cutoff){};
  double doFilter(const double &);
};

// Tilt-Coordinationのローパスフィルタ
class Sample_tLPF : public MotionFilter {
private:
  // ダンピング係数
  double damp;

public:
  explicit Sample_tLPF(unsigned int t_ms, const double &cutoff,
                       const double &dmp)
      : MotionFilter(t_ms, cutoff), damp(dmp){};
  double doFilter(const double &);
};

// Rotationのハイパスフィルタ
class Sample_rHPF : public MotionFilter {
public:
  explicit Sample_rHPF(unsigned int t_ms, const double &cutoff)
      : MotionFilter(t_ms, cutoff){};
  double doFilter(const double &);
};
