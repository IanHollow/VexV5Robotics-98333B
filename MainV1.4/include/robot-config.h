using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor BaseRight;
extern motor BaseLeft;
extern motor LiftRightBack;
extern motor LiftRightFront;
extern motor LiftLeftFront;
extern motor LiftLeftBack;
extern motor ArmRight;
extern motor ArmLeft;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );