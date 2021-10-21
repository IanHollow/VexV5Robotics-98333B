#include "driveControl.h"
#include "vex.h"

int absoluteV(int num) {
  return num < 0 ? -num : num;
}

void driveControlStart() {
  while(true) {

    int rightStick = Controller1.Axis2.position();
    int leftStick = Controller1.Axis3.position();
    int rightStickAbs = absoluteV(Controller1.Axis2.position());
    int leftStickAbs = absoluteV(Controller1.Axis3.position());

    

  }
}