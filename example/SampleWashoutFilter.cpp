#include "SampleWashoutFilter.h"
#include "JAXAFilter.h"

SampleWashoutFilter::SampleWashoutFilter(const double &interval_ms) {
  double breakFrequencyForHighPass = 2.5; // ωn ：折れ点周波数（ハイパス）
  double breakFrequencyForLowPass =
      2 * breakFrequencyForHighPass; // ωLP：折れ点周波数（ローパス）
  double dampingRatio = 1;           // ζLP：ダンピング係数

  Filter *tHPF[3];
  Filter *rLPF[2];
  Filter *rHPF[3];

  // Translationのハイパスフィルタ
  tHPF[0] = new JAXA_tHPF(interval_ms, breakFrequencyForHighPass);
  tHPF[1] = new JAXA_tHPF(interval_ms, breakFrequencyForHighPass);
  tHPF[2] = new JAXA_tHPF(interval_ms, breakFrequencyForHighPass);

  // Tilt-Coordinationのローパスフィルタ
  rLPF[0] = new JAXA_tLPF(interval_ms, breakFrequencyForLowPass, dampingRatio);
  rLPF[1] = new JAXA_tLPF(interval_ms, breakFrequencyForLowPass, dampingRatio);

  // Rotationのハイパスフィルタ
  rHPF[0] = new JAXA_rHPF(interval_ms, breakFrequencyForHighPass);
  rHPF[1] = new JAXA_rHPF(interval_ms, breakFrequencyForHighPass);
  rHPF[2] = new JAXA_rHPF(interval_ms, breakFrequencyForHighPass);

  washout = new WashoutFilter(tHPF, rLPF, rHPF, interval_ms);
}

SampleWashoutFilter::~SampleWashoutFilter() { delete washout; }

Position SampleWashoutFilter::calculateSimulatorPosition(Motion &motion) {
  return washout->calculateSimulatorPosition(motion);
}
