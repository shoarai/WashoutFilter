#include "../src/Washout.h"
#include "unistd.h"
#include <iostream>

using namespace std;

unsigned int interval = 10;
Washout washout(interval);

int main() {
  for (size_t i = 0; i < 4; i++) {
    washout.doFilter(0, 1, 2, 3, 4, 5);

    cout << "x: " << washout.getx() << '\n';
    cout << "y: " << washout.gety() << '\n';
    cout << "z: " << washout.getz() << '\n';
    cout << "phi: " << washout.getPhi() << '\n';
    cout << "theta: " << washout.getSit() << '\n';
    cout << "psi: " << washout.getPsi() << '\n';
    sleep(1);
  }

  cout << "end" << '\n';
  return 0;
}
