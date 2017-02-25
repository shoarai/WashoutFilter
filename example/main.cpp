#include "../src/Washout.h"
#include "unistd.h"
#include <iostream>

using namespace std;

unsigned int interval = 10;
Washout washout(interval);

int main() {
  for (size_t i = 0; i < 4; i++) {
    Position position = washout.doFilter(0, 1, 2, 3, 4, 5);

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
