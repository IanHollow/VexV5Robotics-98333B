#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor BaseFrontLeft = motor(PORT12, ratio18_1, false);
motor BaseBackLeft = motor(PORT2, ratio18_1, false);
motor BaseFrontRight = motor(PORT11, ratio18_1, true);
motor BaseBackRight = motor(PORT4, ratio18_1, true);
motor LiftLeftBack = motor(PORT5, ratio36_1, false);
motor LiftLeftFront = motor(PORT6, ratio36_1, false);
motor LiftRightBack = motor(PORT7, ratio36_1, true);
motor LiftRightFront = motor(PORT8, ratio36_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
    // nothing to initialize
}