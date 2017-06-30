// Copyright (c) 2017 shoarai

#include "SampleWashoutFilter.h"
#include "SampleFilter.h"
#include <iostream>

SampleWashoutFilter::SampleWashoutFilter(const double &interval_ms)
{
  const double breakFrequencyForHighPass = 2.5;                          // ωn
  const double breakFrequencyForLowPass = 2 * breakFrequencyForHighPass; // ωLP
  const double dampingingRatio = 1;                                      // ζLP

  int translationHighPassFilterNum = 3;
  int translationLowPassFilterNum = 2;
  int rotationHighPassFilterNum = 3;

  IFilter *tHPFs[translationHighPassFilterNum];
  IFilter *rLPFs[translationLowPassFilterNum];
  IFilter *rHPFs[rotationHighPassFilterNum];

  for (int i = 0; i < translationHighPassFilterNum; i++)
  {
    tHPFs[i] = new Sample_translationHighPassFilter(
        interval_ms, breakFrequencyForHighPass);
  }
  for (int i = 0; i < translationLowPassFilterNum; i++)
  {
    rLPFs[i] = new Sample_translationLowPassFilter(
        interval_ms, breakFrequencyForLowPass, dampingingRatio);
  }
  for (int i = 0; i < rotationHighPassFilterNum; i++)
  {
    rHPFs[i] = new Sample_rotaionHighPassFilter(
        interval_ms, breakFrequencyForHighPass);
  }

  washout = new WashoutFilter(tHPFs, rLPFs, rHPFs, interval_ms);
}

SampleWashoutFilter::~SampleWashoutFilter() { delete washout; }

Position SampleWashoutFilter::doFilter(Motion &motion)
{
  return washout->doFilter(motion);
}
