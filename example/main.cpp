#include "../src/WashoutFilter.h"
#include "unistd.h"
#include <iostream>

using namespace std;

unsigned int interval = 10;

int main() {
  // x: 0
  // y: 9.75461e-05
  // z: -0.956405
  // phi: 0.0296297
  // theta: 0.0395062
  // psi: 0.0493827
  WashoutFilter washout(interval);

  for (size_t i = 0; i < 4; i++) {
    Position position = washout.calculateSimulatorPosition(0, 1, 2, 3, 4, 5);

    cout << "x: " << position.getTranslationX() << '\n';
    cout << "y: " << position.getTranslationY() << '\n';
    cout << "z: " << position.getTranslationZ() << '\n';
    cout << "phi: " << position.getRotationX() << '\n';
    cout << "theta: " << position.getRotationY() << '\n';
    cout << "psi: " << position.getRotationZ() << '\n';
    sleep(1);
  }

  cout << "end" << '\n';
  return 0;
}
