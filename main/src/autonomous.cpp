/*#include "autonomous.h"
#include "vex.h"

int tolerance = 20;

const int visCenter = 158;
// const int visWidth = 316;

// Pre-Define Functions
bool alignedWithGoal(signature);
void alignWithGoal(signature);
bool closeToGoal(signature);
void driveForward();
void rotateLeft();
void rotateRight();
void pickUpGoal();

void liftHold()
{
    while (true)
    {
        Lift.stop(hold); // Lock Lift
        wait(100, msec);
    }
}

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
    // Set Velocity
    Base.setVelocity(100, pct);
    Lift.setVelocity(100, pct);
    Arm.setVelocity(100, pct);

    Lift.spinFor(forward, 4, rev);
    Lift.spinFor(reverse, 4, rev);

    thread holdLift(liftHold);

    // Drive Forward
    Base.spinFor(forward, 1.25, rev);

    // Drive to Yellow Goal & pickup
    driveToGoal(VisionSensor__YGOAL);

    // Push Goal
    Base.spinFor(forward, 3, rev);

    // Turn to next Goal
    Arm.spinFor(forward, 0.5, rev);

    BaseLeft.spinFor(reverse, 0.25, rev, false);
    BaseRight.spinFor(forward, 0.25, rev);

    Base.spinFor(forward, 0.5, rev);

    Arm.spinFor(reverse, 0.5, rev);

    Base.spinFor(reverse, 0.5, rev);

    BaseLeft.spinFor(forward, 1, rev, false);
    BaseRight.spinFor(reverse, 1, rev);

    Base.spinFor(forward, 0.5, rev);

    // Drive to Yellow Goal & pickup
    driveToGoal(VisionSensor__YGOAL);

    Arm.spinFor(forward, 0.5, rev);

    Base.spinFor(forward, 3, rev);

    Arm.spinFor(reverse, 0.5, rev);

    BaseLeft.spinFor(reverse, 1, rev, false);
    BaseRight.spinFor(forward, 1, rev);

    // Drive to Yellow Goal & pickup
    driveToGoal(VisionSensor__YGOAL);

    Arm.spinFor(forward, 0.5, rev);

    Base.spinFor(forward, 3, rev);

    Arm.spinFor(reverse, 0.5, rev);
}

void driveToGoal(signature goalSig)
{
    while (true)
    {
        VisionSensor.takeSnapshot(goalSig);

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        if (VisionSensor.largestObject.exists)
        { // Check if the object exists
            if ((VisionSensor.largestObject.originX + VisionSensor.largestObject.width) > (visCenter))
            { // Is X location of object + width > center screen then rotate counterclockwise
                rotateRight();
                Brain.Screen.print("Go Right");
            }
            else if ((VisionSensor.largestObject.originX + VisionSensor.largestObject.width) <
                     (visCenter - 2 * tolerance))
            { // Is X location of object + width < center screen then rotate clockwise
                rotateLeft();
                Brain.Screen.print("Go Left");
            }
            else
            {
                Brain.Screen.print("Centered");
                Base.stop(coast);
                if (closeToGoal(goalSig))
                {
                    Brain.Screen.setCursor(2, 1);
                    Brain.Screen.print("Close to Goal");
                    Base.stop();
                    return;
                }
                else
                {
                    driveForward();
                    wait(20, msec);
                }
            }
        }
        else
        {
            Brain.Screen.print("No Object");
        }

        wait(100, msec);
    }
}

void pickUpGoal()
{
    Base.setVelocity(100, pct);
    Base.spinFor(forward, 0.9, rev);
    Arm.setVelocity(100, pct);
    Arm.spinFor(forward, 1.25, rev);
    Arm.setVelocity(100, pct);
    Arm.spinFor(forward, 2, rev);
    wait(500, msec);
    Arm.spinFor(reverse, 3.25, rev);
}

bool closeToGoal(signature goalSig)
{ // Is the Goal close enough?
    return VisionSensor.largestObject.width > 130;
}

void driveForward()
{ // Drive Forward
    Base.spin(forward, 50, pct);
}

void rotateLeft()
{ // Rotate Counterclockwise
    BaseRight.spin(forward, 30, pct);
    BaseLeft.spin(reverse, 30, pct);
}

void rotateRight()
{ // Rotate Clockwise
    BaseRight.spin(reverse, 30, pct);
    BaseLeft.spin(forward, 30, pct);
}*/