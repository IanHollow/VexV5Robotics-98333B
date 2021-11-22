#include "autonomous.h"
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

// Base.setVelocity(75, pct);
// Arm.setVelocity(75, pct);
// Base.spinFor(forward, 1, rev);
// Arm.spinFor(forward, 1.75, rev, false);
// BaseRight.spinFor(forward, 1.45, rev);
// Arm.spinFor(forward, 1.75, rev, false);

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
    driveToGoal(VisionSensor__YGOAL);
    pickUpGoal();
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
                    Base.setVelocity(50, pct);
                    Base.spinFor(forward, 2, rev);
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
    Arm.setVelocity(50, pct);
    Arm.spinFor(forward, 1.75, rev);
}

bool closeToGoal(signature goalSig)
{ // Is the Goal close enough?
    return VisionSensor.largestObject.width > 100;
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
}