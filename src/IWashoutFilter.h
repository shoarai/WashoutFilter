// Copyright (c) 2017 shoarai

#include "Motion.h"
#include "Position.h"

class IWashoutFilter {
public:
  virtual Position doFilter(Motion &motion) = 0;
};
