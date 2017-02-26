// Copyright (c) 2017 shoarai

#include "Motion.h"
#include "Position.h"

class MotionDriveAlgorithm {
public:
  virtual Position calculateSimulatorPosition(Motion &motion) = 0;
};
