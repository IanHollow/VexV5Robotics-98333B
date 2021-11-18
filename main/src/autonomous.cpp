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

void pickUpGoal(signature);

// Base.setVelocity(75, pct);
// Arm.setVelocity(75, pct);
// Base.spinFor(forward, 1, rev);
// Arm.spinFor(forward, 1.75, rev, false);
// BaseRight.spinFor(forward, 1.45, rev);
// Arm.spinFor(forward, 1.75, rev, false);

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
    driveToGoal(Vision__YGOAL);
    pickUpGoal(Vision__YGOAL);
}

void driveToGoal(signature goalSig)
{
    while (true)
    {
        Vision.takeSnapshot(goalSig);

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        if (Vision.largestObject.exists)
        {
            if ((Vision.largestObject.originX + Vision.largestObject.width) > (visCenter))
            {
                rotateRight();
                Brain.Screen.print("Go Right");
            }
            else if ((Vision.largestObject.originX + Vision.largestObject.width) < (visCenter - 2 * tolerance))
            {
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
                    Base.stop(coast);
                    Base.setVelocity(50, pct);
                    Base.spinFor(forward, 2, rev);
                    return;
                }
                else
                {
                    driveForward();
                    wait(100, msec);
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

void pickUpGoal(signature)
{
    while (true)
    {
        Arm.setVelocity(50, pct);
        Arm.spinFor(forward, 1.75, rev);
    }
}

bool closeToGoal(signature goalSig)
{ // Is the Goal close enough?
    return Vision.largestObject.width > 70;
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