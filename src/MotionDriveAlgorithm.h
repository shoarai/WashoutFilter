#include "Position.h"

class MotionDriveAlgorithm {
public:
  virtual Position calculateSimulatorPosition(const double &, const double &,
                                              const double &, const double &,
                                              const double &,
                                              const double &) = 0;
};
