#include "vex.h"

// Motor Groups
motor_group Base = motor_group(BaseFrontRight, BaseBackRight, BaseFrontLeft, BaseBackLeft);
motor_group BaseRight = motor_group(BaseFrontRight, BaseBackRight);
motor_group BaseLeft = motor_group(BaseFrontLeft, BaseBackLeft);
motor_group Lift = motor_group(LiftRightBack, LiftRightFront, LiftLeftBack, LiftLeftFront);
motor_group LiftLeft = motor_group(LiftLeftBack, LiftLeftFront);
motor_group LiftRight = motor_group(LiftRightBack, LiftRightFront);

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
            Lift.spin(forward, 100, pct);
        }
        else if (buttonL2)
        {
            Lift.spin(reverse, 100, pct);
        }
        else
        {
            Lift.stop(hold);
        }

        wait(20, msec);
    }
}