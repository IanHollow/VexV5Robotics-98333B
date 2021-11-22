#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor BaseRight = motor(PORT1, ratio36_1, true);
motor BaseLeft = motor(PORT2, ratio36_1, false);
motor LiftRightBack = motor(PORT3, ratio36_1, true);
motor LiftRightFront = motor(PORT4, ratio36_1, true);
motor LiftLeftFront = motor(PORT6, ratio36_1, false);
motor LiftLeftBack = motor(PORT7, ratio36_1, false);
motor ArmRight = motor(PORT9, ratio36_1, true);
motor ArmLeft = motor(PORT8, ratio36_1, false);
limit LimitLeftFront = limit(Brain.ThreeWirePort.A);
limit LimitRightFront = limit(Brain.ThreeWirePort.B);
limit LimitLeftBack = limit(Brain.ThreeWirePort.C);
limit LimitRightBack = limit(Brain.ThreeWirePort.D);
/*vex-vision-config:begin*/
signature VisionSensor__BGOAL = signature (1, -2217, -1597, -1908, 5553, 6491, 6022, 2.5, 0);
signature VisionSensor__YGOAL = signature (2, 1135, 2365, 1750, -3405, -2893, -3150, 2.5, 0);
vision VisionSensor = vision (PORT10, 45, VisionSensor__BGOAL, VisionSensor__YGOAL);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}