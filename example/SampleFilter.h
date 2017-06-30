// Copyright (c) 2017 shoarai

#include "../src/MotionFilter.h"

class Sample_translationHighPassFilter : public MotionFilter
{
public:
  explicit Sample_translationHighPassFilter(unsigned int t_ms, const double &cutoff)
      : MotionFilter(t_ms, cutoff){};
  double doFilter(const double &);
};

class Sample_translationLowPassFilter : public MotionFilter
{
private:
  // Dampinging coefficient
  double damping;

public:
  explicit Sample_translationLowPassFilter(unsigned int t_ms, const double &cutoff,
                                           const double &dmp)
      : MotionFilter(t_ms, cutoff), damping(dmp){};
  double doFilter(const double &);
};

class Sample_rotaionHighPassFilter : public MotionFilter
{
public:
  explicit Sample_rotaionHighPassFilter(unsigned int t_ms, const double &cutoff)
      : MotionFilter(t_ms, cutoff){};
  double doFilter(const double &);
};
