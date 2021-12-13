#include "vex.h"

// Motor Groups
motor_group Base = motor_group(BaseLeft, BaseRight);
motor_group Lift = motor_group(LiftRightBack, LiftRightFront, LiftLeftBack, LiftLeftFront);
motor_group LiftLeft = motor_group(LiftLeftBack, LiftLeftFront);
motor_group LiftRight = motor_group(LiftRightBack, LiftRightFront);
motor_group Arm = motor_group(ArmRight, ArmLeft);

void driveControlStart()
{
    while (true)
    {
        // Controller Sticks
        int rightStick = Controller1.Axis2.position();
        int leftStick = Controller1.Axis3.position();
        int rightStickAbs = abs(Controller1.Axis2.position());
        int leftStickAbs = abs(Controller1.Axis3.position());

        // Controller Buttons
        bool buttonL1 = Controller1.ButtonL1.pressing();
        bool buttonL2 = Controller1.ButtonL2.pressing();
        bool buttonR1 = Controller1.ButtonR1.pressing();
        bool buttonR2 = Controller1.ButtonR2.pressing();
        bool buttonB = Controller1.ButtonB.pressing();

        // Limit Switches
        bool stopLiftBackLeft = LimitLeftBack.pressing();
        bool stopLiftBackRight = LimitRightBack.pressing();
        bool stopLiftFrontLeft = LimitLeftFront.pressing();
        bool stopLiftFrontRight = LimitRightFront.pressing();

        // Drive Base
        if (rightStickAbs > 5)
        {
            BaseRight.spin(rightStick < 0 ? reverse : forward, rightStickAbs, pct);
        }
        else
        {
            BaseRight.stop(coast);
        }

        if (leftStickAbs > 5)
        {
            BaseLeft.spin(leftStick < 0 ? reverse : forward, leftStickAbs, pct);
        }
        else
        {
            BaseLeft.stop(coast);
        }

        // Lift
        if (buttonL1)
        {
            stopLiftFrontLeft ? LiftLeft.stop(hold) : LiftLeft.spin(forward, 100, pct);
            stopLiftFrontRight ? LiftRight.stop(hold) : LiftRight.spin(forward, 100, pct);
        }
        else if (buttonL2)
        {
            stopLiftBackLeft ? LiftLeft.stop(hold) : LiftLeft.spin(reverse, 100, pct);
            stopLiftBackRight ? LiftRight.stop(hold) : LiftRight.spin(reverse, 100, pct);
        }
        else
        {
            Lift.stop(hold);
        }

        // Arm
        if (buttonR1 || buttonR2)
        {
            Arm.spin(buttonR1 ? forward : reverse, (buttonR2 || buttonB) ? 100 : 30, pct);
        }
        else
        {
            Arm.stop(hold);
        }

        wait(20, msec);
    }
}