#include "Filter.h"

class MotionFilter : public Filter {
protected:
  // データ遅れ
  enum enDELAY { DELAY_0 = 0, DELAY_1, DELAY_2, DELAY_MAX };

  unsigned int time_ms; // サンプリング間隔[ms]
  double cutoffFre;     // 折点角周波数

  double input[DELAY_MAX];  // 入力値
  double output[DELAY_MAX]; // 出力値

  template <class T> inline T square(const T &x) { return ((x) * (x)); }

public:
  explicit MotionFilter(unsigned int t, const double &cutoff);
  virtual ~MotionFilter(){};
};
