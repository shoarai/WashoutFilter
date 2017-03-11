// Copyright (c) 2017 shoarai

#include "SampleWashoutFilter.h"
#include "SampleFilter.h"
#include <iostream>

SampleWashoutFilter::SampleWashoutFilter(const double &interval_ms) {
  double breakFrequencyForHighPass = 2.5; // ωn: 折れ点周波数（ハイパス）
  double breakFrequencyForLowPass =
      2 * breakFrequencyForHighPass; // ωLP: 折れ点周波数（ローパス）
  double dampingRatio = 1;           // ζLP: ダンピング係数

  int translationHighPassFilterNum = 3;
  int translationLowPassFilterNum = 2;
  int rotationHighPassFilterNum = 3;

  Filter *tHPFs[translationHighPassFilterNum];
  Filter *rLPFs[translationLowPassFilterNum];
  Filter *rHPFs[rotationHighPassFilterNum];

  for (int i = 0; i < translationHighPassFilterNum; i++) {
    tHPFs[i] = new Sample_tHPF(interval_ms, breakFrequencyForHighPass);
  }
  for (int i = 0; i < translationLowPassFilterNum; i++) {
    rLPFs[i] =
        new Sample_tLPF(interval_ms, breakFrequencyForLowPass, dampingRatio);
  }
  for (int i = 0; i < rotationHighPassFilterNum; i++) {
    rHPFs[i] = new Sample_rHPF(interval_ms, breakFrequencyForHighPass);
  }

  washout = new WashoutFilter(tHPFs, rLPFs, rHPFs, interval_ms);
}

SampleWashoutFilter::~SampleWashoutFilter() { delete washout; }

Position SampleWashoutFilter::doFilter(Motion &motion) {
  return washout->doFilter(motion);
}
