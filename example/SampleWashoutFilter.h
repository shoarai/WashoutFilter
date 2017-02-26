#include "../src/WashoutFilter.h"

class SampleWashoutFilter : public MotionDriveAlgorithm {
public:
  SampleWashoutFilter(const double &interval_ms);
  ~SampleWashoutFilter();
  Position calculateSimulatorPosition(Motion &motion);

private:
  WashoutFilter *washout;
};
