using namespace vex;

extern brain Brain;

using signature = vision::signature;

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
extern limit LimitLeftFront;
extern limit LimitRightFront;
extern limit LimitLeftBack;
extern limit LimitRightBack;
extern signature VisionSensor__BGOAL;
extern signature VisionSensor__YGOAL;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);