#include "SampleFilter.h"

// 機能		：Translationのハイパスフィルタ
double Sample_tHPF::doFilter(const double &input0) {
  // 入力値に引数を代入
  input[DELAY_0] = input0;

  // T[s]×ωn
  double T_w = cutoffFre * time_ms / 1000;

  // 差分方程式を解く
  output[DELAY_0] = square(2 / (T_w + 2)) *
                        (input[DELAY_0] - 2 * input[DELAY_1] + input[DELAY_2]) -
                    2 * (T_w - 2) / (T_w + 2) * output[DELAY_1] -
                    square((T_w - 2) / (T_w + 2)) * output[DELAY_2];

  // 入力値と出力値を一つ遅らせる
  for (int i = 0; i < 2; i++) {
    input[2 - i] = input[1 - i];
    output[2 - i] = output[1 - i];
  }

  return output[0];
}

// 機能		：Tilt-coordinationのローパスフィルタ
double Sample_tLPF::doFilter(const double &input0) {
  // 入力値に引数を代入
  input[DELAY_0] = input0;

  // (TωLP)^2、4ζωLP*T
  double T2w2 = square(cutoffFre * time_ms / 1000);
  double dw4T = 4 * damp * cutoffFre * time_ms / 1000;

  // 差分方程式を解く
  output[DELAY_0] =
      (T2w2) / (T2w2 + dw4T + 4) *
          (input[DELAY_0] + 2 * input[DELAY_1] + input[DELAY_2]) -
      (1 / (T2w2 + dw4T + 4)) * (2 * (T2w2 - 4) * output[DELAY_1] +
                                 (T2w2 - dw4T + 4) * output[DELAY_2]);

  // 入力値と出力値を一つ遅らせる
  for (int i = 0; i < 2; i++) {
    input[2 - i] = input[1 - i];
    output[2 - i] = output[1 - i];
  }

  return output[0];
}

// 機能		：Rotationのハイパスフィルタ
double Sample_rHPF::doFilter(const double &input0) {
  // 入力値に引数を代入
  input[DELAY_0] = input0;

  // Tωn
  double Tw = cutoffFre * time_ms / 1000;

  // 差分方程式を解く
  output[DELAY_0] = 2 / (Tw + 2) * (input[DELAY_0] - input[DELAY_1]) -
                    (Tw - 2) / (Tw + 2) * output[DELAY_1];

  // 入力値と出力値を一つ遅らせる
  input[1] = input[0];
  output[1] = output[0];

  return output[0];
}
