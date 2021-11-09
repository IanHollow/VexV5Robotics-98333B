#include "autonomous.h"
#include "vex.h"

int tolerance = 10;
int autoVelocity = 50;

const int visWidth = 316;

vex::vision::object largestObj = Vision.largestObject;

// Pre-Define Functions
bool alignedWithGoal(signature);
bool closeToGoal(signature);
void driveForward();
void rotateLeft();
void rotateRight();

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
}

void driveToGoal(signature goalSig)
{
    while (!largestObj.exists)
    { // Try to Face the Goal

        rotateLeft();

        wait(20, msec);
    }
    Base.stop(coast);

    while (true)
    { // Center the Goal and Drive to it

        if (alignedWithGoal(goalSig))
        {
            if (!closeToGoal(goalSig))
            {
                driveForward();
            }
            else
            {
                Base.stop(coast);
                return; // Finished: Ready to Pick Up Goal
            }
        }

        wait(20, msec);
    }
}

bool alignedWithGoal(signature goalSig)
{ // Is the Goal centered?

    Vision.takeSnapshot(goalSig);

    if (largestObj.exists)
    {
        const int farRightXPos = largestObj.centerX + largestObj.width;
        const int assumedCenterXPos = (visWidth / 2) + (largestObj.width / 2);

        if (farRightXPos > (assumedCenterXPos + tolerance))
        {
            rotateLeft();
        }
        else if (farRightXPos < (assumedCenterXPos + tolerance))
        {
            rotateRight();
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool closeToGoal(signature goalSig)
{ // Is the Goal close enough?
    return largestObj.width >= (visWidth * 3 / 4);
}

void driveForward()
{ // Drive Forward
    Base.spin(forward, autoVelocity, pct);
}

void rotateLeft()
{ // Rotate Counterclockwise
    BaseRight.spin(forward, autoVelocity, pct);
    BaseLeft.spin(reverse, autoVelocity, pct);
}

void rotateRight()
{ // Rotate Clockwise
    BaseRight.spin(reverse, autoVelocity, pct);
    BaseLeft.spin(forward, autoVelocity, pct);
}