// Copyright (c) 2017 shoarai

#include "SampleWashoutFilter.h"

#include <array>

#include "SampleFilter.h"
#include <iostream>

namespace WashoutFilter
{
SampleWashoutFilter::SampleWashoutFilter(const double &interval_ms)
{
  const double breakFrequencyForHighPass = 2.5;                          // ωn
  const double breakFrequencyForLowPass = 2 * breakFrequencyForHighPass; // ωLP
  const double dampingingRatio = 1;                                      // ζLP

  const int translationHighPassFilterNum = 3;
  const int translationLowPassFilterNum = 2;
  const int rotationHighPassFilterNum = 3;

  std::array<std::shared_ptr<IFilter>, translationHighPassFilterNum> tHPFs;
  std::array<std::shared_ptr<IFilter>, translationLowPassFilterNum> rLPFs;
  std::array<std::shared_ptr<IFilter>, rotationHighPassFilterNum> rHPFs;

  for (int i = 0; i < translationHighPassFilterNum; i++)
  {
	  tHPFs[i] = std::make_shared<Sample_translationHighPassFilter>(
		  interval_ms, breakFrequencyForHighPass);
  }
  for (int i = 0; i < translationLowPassFilterNum; i++)
  {
	  rLPFs[i] = std::make_shared<Sample_translationLowPassFilter>(
		  interval_ms, breakFrequencyForLowPass, dampingingRatio);
  }
  for (int i = 0; i < rotationHighPassFilterNum; i++)
  {
	  rHPFs[i] = std::make_shared<Sample_rotaionHighPassFilter>(
		  interval_ms, breakFrequencyForHighPass);
  }

  washout = std::make_shared<WashoutFilter>(tHPFs, rLPFs, rHPFs, interval_ms);
}

SampleWashoutFilter::~SampleWashoutFilter()
{
}

Position SampleWashoutFilter::doFilter(Motion &motion)
{
  return washout->doFilter(motion);
}
}
