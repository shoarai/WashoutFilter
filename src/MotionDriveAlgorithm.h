#include "Motion.h"
#include "Position.h"

class MotionDriveAlgorithm {
public:
  virtual Position calculateSimulatorPosition(Motion &motion) = 0;
};
