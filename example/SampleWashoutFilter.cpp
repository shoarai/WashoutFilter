// Copyright (c) 2017 shoarai

#include "SampleWashoutFilter.h"
#include "SampleFilter.h"

SampleWashoutFilter::SampleWashoutFilter(const double &interval_ms) {
  double breakFrequencyForHighPass = 2.5; // ωn: 折れ点周波数（ハイパス）
  double breakFrequencyForLowPass =
      2 * breakFrequencyForHighPass; // ωLP: 折れ点周波数（ローパス）
  double dampingRatio = 1;           // ζLP: ダンピング係数

  int translationHighPassFilterNum = 3;
  int translationLowPassFilterNum = 2;
  int rotationHighPassFilterNum = 3;

  Filter *tHPF[translationHighPassFilterNum];
  Filter *rLPF[translationLowPassFilterNum];
  Filter *rHPF[rotationHighPassFilterNum];

  for (int i = 0; i < translationHighPassFilterNum; i++) {
    tHPF[i] = new Sample_tHPF(interval_ms, breakFrequencyForHighPass);
  }
  for (int i = 0; i < translationLowPassFilterNum; i++) {
    rLPF[i] =
        new Sample_tLPF(interval_ms, breakFrequencyForLowPass, dampingRatio);
  }
  for (int i = 0; i < rotationHighPassFilterNum; i++) {
    rHPF[i] = new Sample_rHPF(interval_ms, breakFrequencyForHighPass);
  }

  washout = new WashoutFilter(tHPF, rLPF, rHPF, interval_ms);
}

SampleWashoutFilter::~SampleWashoutFilter() { delete washout; }

Position SampleWashoutFilter::calculateSimulatorPosition(Motion &motion) {
  return washout->calculateSimulatorPosition(motion);
}
