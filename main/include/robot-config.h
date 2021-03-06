using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor BaseFrontLeft;
extern motor BaseBackLeft;
extern motor BaseFrontRight;
extern motor BaseBackRight;
extern motor LiftLeftBack;
extern motor LiftLeftFront;
extern motor LiftRightBack;
extern motor LiftRightFront;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );