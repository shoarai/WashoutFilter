#include "Filter.h"

// Translationのハイパスフィルタ
class JAXA_tHPF : public Filter {
public:
  // コンストラクタ
  explicit JAXA_tHPF(unsigned int t_ms, const double &cutoff)
      : Filter(t_ms, cutoff){};

  // フィルタリング
  double doFilter(const double &);
};

// Tilt-Coordinationのローパスフィルタ
class JAXA_tLPF : public Filter {
private:
  // ダンピング係数
  double damp;

public:
  // コンストラクタ
  explicit JAXA_tLPF(unsigned int t_ms, const double &cutoff, const double &dmp)
      : Filter(t_ms, cutoff), damp(dmp){};

  // フィルタリング
  double doFilter(const double &);
};

// Rotationのハイパスフィルタ
class JAXA_rHPF : public Filter {
public:
  // コンストラクタ
  explicit JAXA_rHPF(unsigned int t_ms, const double &cutoff)
      : Filter(t_ms, cutoff){};

  // フィルタリング
  double doFilter(const double &);
};
