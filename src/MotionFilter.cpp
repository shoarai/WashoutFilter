// Copyright (c) 2017 shoarai

#include "MotionFilter.h"

MotionFilter::MotionFilter(unsigned int t_ms, const double &cutoff)
    : time_ms(t_ms), cutoffFrequency(cutoff)
{
  for (int i = 0; i < DELAY_MAX; i++)
  {
    input[i] = output[i] = 0;
  }
}
