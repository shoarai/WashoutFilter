// Copyright (c) 2017 shoarai

#include "SampleFilter.h"

double Sample_translationHighPassFilter::doFilter(const double &input0)
{
  input[DELAY_0] = input0;

  // T[s]×ωn
  double T_w = cutoffFrequency * time_ms / 1000;

  // Solve difference equation
  output[DELAY_0] =
      square(2 / (T_w + 2)) * (input[DELAY_0] - 2 * input[DELAY_1] + input[DELAY_2]) -
      2 * (T_w - 2) / (T_w + 2) * output[DELAY_1] -
      square((T_w - 2) / (T_w + 2)) * output[DELAY_2];

  // Delay
  for (int i = 0; i < 2; i++)
  {
    input[2 - i] = input[1 - i];
    output[2 - i] = output[1 - i];
  }

  return output[0];
}

double Sample_translationLowPassFilter::doFilter(const double &input0)
{
  input[DELAY_0] = input0;

  // (TωLP)^2、4ζωLP*T
  double T2w2 = square(cutoffFrequency * time_ms / 1000);
  double dw4T = 4 * damping * cutoffFrequency * time_ms / 1000;

  // Solve difference equation
  output[DELAY_0] =
      (T2w2) / (T2w2 + dw4T + 4) *
          (input[DELAY_0] + 2 * input[DELAY_1] + input[DELAY_2]) -
      (1 / (T2w2 + dw4T + 4)) * (2 * (T2w2 - 4) * output[DELAY_1] +
                                 (T2w2 - dw4T + 4) * output[DELAY_2]);

  // Delay
  for (int i = 0; i < 2; i++)
  {
    input[2 - i] = input[1 - i];
    output[2 - i] = output[1 - i];
  }

  return output[0];
}

double Sample_rotaionHighPassFilter::doFilter(const double &input0)
{
  input[DELAY_0] = input0;

  // Tωn
  double Tw = cutoffFrequency * time_ms / 1000;

  // Solve difference equation
  output[DELAY_0] = 2 / (Tw + 2) * (input[DELAY_0] - input[DELAY_1]) -
                    (Tw - 2) / (Tw + 2) * output[DELAY_1];

  // Delay
  input[1] = input[0];
  output[1] = output[0];

  return output[0];
}
