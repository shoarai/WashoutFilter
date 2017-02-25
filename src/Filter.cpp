#include "Filter.h"

Filter::Filter(unsigned int t_ms, const double &cutoff)
    : time_ms(t_ms), cutoffFre(cutoff) {
  for (int i = 0; i < DELAY_MAX; i++) {
    input[i] = output[i] = 0;
  }
}
