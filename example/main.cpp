#include "../src/WashoutFilter.h"
#include "JAXAFilter.h"
#include "unistd.h"
#include <iostream>

using namespace std;

unsigned int interval = 10;

int main() {
  // x: 0
  // y: 9.75461e-05
  // z: -0.956405
  // phi: 0.0296297
  // theta: 0.0395062
  // psi: 0.0493827

  // フィルタ変数
  double freq_wn = 2.5;          // ωn ：折れ点周波数（ハイパス）
  double freq_wlp = 2 * freq_wn; // ωLP：折れ点周波数（ローパス）
  double damp = 1;               // ζLP：ダンピング係数
  double interval_ms = 10;

  Filter *tHPF[3];
  Filter *rLPF[2];
  Filter *rHPF[3];

  // shared_ptr<Filter> translationHighPassFilter;
  // translationHighPassFilter = make_shared<JAXA_tHPF>(interval_ms, freq_wn);

  // Translationのハイパスフィルタ
  tHPF[0] = new JAXA_tHPF(interval_ms, freq_wn);
  tHPF[1] = new JAXA_tHPF(interval_ms, freq_wn);
  tHPF[2] = new JAXA_tHPF(interval_ms, freq_wn);

  // Tilt-Coordinationのローパスフィルタ
  rLPF[0] = new JAXA_tLPF(interval_ms, freq_wlp, damp);
  rLPF[1] = new JAXA_tLPF(interval_ms, freq_wlp, damp);

  // Rotationのハイパスフィルタ
  rHPF[0] = new JAXA_rHPF(interval_ms, freq_wn);
  rHPF[1] = new JAXA_rHPF(interval_ms, freq_wn);
  rHPF[2] = new JAXA_rHPF(interval_ms, freq_wn);

  WashoutFilter washout(tHPF, rLPF, rHPF, interval_ms);

  // WashoutFilter washout(interval_ms);

  for (size_t i = 0; i < 4; i++) {
    Motion motion(0, 1, 2, 3, 4, 5);
    Position position = washout.calculateSimulatorPosition(motion);

    cout << "x: " << position.getTranslationX() << '\n';
    cout << "y: " << position.getTranslationY() << '\n';
    cout << "z: " << position.getTranslationZ() << '\n';
    cout << "phi: " << position.getRotationX() << '\n';
    cout << "theta: " << position.getRotationY() << '\n';
    cout << "psi: " << position.getRotationZ() << '\n';
    sleep(1);
  }

  cout << "end" << '\n';
  return 0;
}
