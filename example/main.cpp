// Copyright (c) 2017 shoarai

#include "SampleWashoutFilter.h"
#include "unistd.h"
#include <iostream>

using namespace std;

const unsigned int interval_ms = 10;

int main() {
  // x:     0
  // y:     9.75461e-05
  // z:    -0.956405
  // phi: 	0.0296297
  // theta: 0.0395062
  // psi:   0.0493827

  shared_ptr<MotionDriveAlgorithm> motionDrive(
      new SampleWashoutFilter(interval_ms));

  for (int i = 0; i < 4; i++) {
    Motion motion(0, 1, 2, 3, 4, 5);
    Position position = motionDrive->calculateSimulatorPosition(motion);

    cout << "x: \t" << position.getTranslationX() << '\n';
    cout << "y: \t" << position.getTranslationY() << '\n';
    cout << "z: \t" << position.getTranslationZ() << '\n';
    cout << "phi: \t" << position.getRotationX() << '\n';
    cout << "theta: \t" << position.getRotationY() << '\n';
    cout << "psi: \t" << position.getRotationZ() << '\n';
    sleep(1);
  }

  cout << "end" << '\n';
  return 0;
}
