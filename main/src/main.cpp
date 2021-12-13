#include "autonomous.h"
#include "driveControl.h"
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// BaseFrontLeft        motor         1               
// BaseBackLeft         motor         2               
// BaseFrontRight       motor         3               
// BaseBackRight        motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

void telemetry()
{
    while (true)
    {
        int baseRightTemp = BaseRight.temperature(celsius);
        int baseLeftTemp = BaseLeft.temperature(celsius);
        // int LiftRightBackTemp = LiftRightBack.temperature(celsius);
        // int LiftRightFrontTemp = LiftRightFront.temperature(celsius);
        // int LiftLeftBackTemp = LiftLeftBack.temperature(celsius);
        // int LiftLeftFrontTemp = LiftLeftFront.temperature(celsius);

        Controller1.Screen.clearScreen();

        Controller1.Screen.setCursor(1, 0);
        Controller1.Screen.print("B: %d%s%d", baseLeftTemp, " ", baseRightTemp);

        Controller1.Screen.setCursor(2, 0);
        // Controller1.Screen.print("LR: %d%s%d%s%d%s%d", LiftRightBackTemp, " ", LiftRightFrontTemp,
        //                          " LL: ", LiftLeftBackTemp, " ", LiftLeftFrontTemp);

        wait(5000, msec);
    }
}

void pre_auton(void)
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // All activities that occur before the competition starts

    thread controllerScreen(telemetry);
}

void autonomous(void)
{
    //autonomousStart();
}

void usercontrol(void)
{
    driveControlStart();
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        wait(100, msec);
    }
}
