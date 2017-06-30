// Copyright (c) 2017 shoarai

#include "IFilter.h"

class MotionFilter : public IFilter
{
protected:
  enum enDELAY
  {
    DELAY_0 = 0,
    DELAY_1,
    DELAY_2,
    DELAY_MAX
  };

  unsigned int time_ms; // Sampling interval[ms]
  double cutoffFrequency;

  double input[DELAY_MAX];
  double output[DELAY_MAX];

  template <class T>
  inline T square(const T &x) { return ((x) * (x)); }

public:
  explicit MotionFilter(unsigned int t, const double &cutoff);
  virtual ~MotionFilter(){};
};
