// Copyright (c) 2017 shoarai

#include "../src/WashoutFilter.h"

namespace WashoutFilter
{
class SampleWashoutFilter : public IWashoutFilter
{
public:
  SampleWashoutFilter(const double &interval_ms);
  ~SampleWashoutFilter();
  Position doFilter(Motion &motion);

private:
  std::shared_ptr<WashoutFilter> washout;
};
}
