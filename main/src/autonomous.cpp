#include "autonomous.h"
#include "vex.h"
#include "visionCalibration.h"

int tolerance = 10;

const int visCenter = 158;
// const int visWidth = 316;

int curTime = Brain.timer(msec);
bool locateFinshed = false;

// Pre-Define Functions
void driveToGoal(vex::vision::signature);
bool closeToGoal(vex::vision::signature);
void driveForward();
void rotateLeft();
void rotateRight();
void locateYGoal();
void locateRGoal();
void sec15RL();
void autoSkills();
void timedLocate(void (*callback)(void), int);

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
    // Set Velocity
    Base.setVelocity(100, pct);
    Lift.setVelocity(100, pct);

    autoSkills();
}

void sec15RL()
{
    Base.setVelocity(100, pct);

    // Drive Forward
    Base.spinFor(forward, 2.75, rev, false);

    // Lift Deployment
    Lift.spinFor(forward, 4, rev);
    Lift.spinFor(reverse, 4, rev);

    timedLocate(locateYGoal, 5000);

    Lift.setVelocity(75, pct);
    Lift.spinFor(forward, 4, rev, false);

    wait(1, sec);

    Base.spinFor(reverse, locateFinshed ? 5.5 : 8, rev, false);

    wait(1, sec);

    Lift.setVelocity(100, pct);
    Lift.spinFor(reverse, 4, rev);
}

void autoSkills()
{
    Base.setVelocity(100, pct);
    Lift.setVelocity(100, pct);

    // Drive Forward
    BaseLeft.setVelocity(90, pct);
    Base.spinFor(forward, 11.5, rev);

    Base.setVelocity(100, pct);
    Base.spinFor(reverse, 1, rev);

    BaseLeft.spinFor(reverse, 2.3, rev, false);
    BaseRight.spinFor(forward, 2.3, rev);

    driveToGoal(YGOAL);

    Base.spinFor(forward, 7.1, rev);

    Base.spinFor(reverse, 0.75, rev);

    BaseLeft.spinFor(forward, 1.8, rev, false);
    BaseRight.spinFor(reverse, 1.8, rev);

    Base.spinFor(reverse, 0.5, rev);

    driveToGoal(YGOAL);

    Base.spinFor(forward, 6.5, rev);

    Base.spinFor(reverse, 1, rev);

    BaseLeft.spinFor(reverse, 1.5, rev, false);
    BaseRight.spinFor(forward, 1.5, rev);

    driveToGoal(YGOAL);

    Base.spinFor(forward, 5, rev);
    BaseRight.spinFor(forward, 1.75, rev);
    Base.spinFor(forward, 1, rev);

    Base.spinFor(reverse, 2, rev);

    BaseLeft.spinFor(forward, 2.8, rev, false);
    BaseRight.spinFor(reverse, 2.8, rev);

    Base.spinFor(reverse, 1, rev);

    Base.spinFor(forward, 1, rev, false);
    Lift.spinFor(forward, 4, rev);
    Lift.spinFor(reverse, 4, rev);
    Base.spinFor(forward, 1, rev);

    driveToGoal(RGOAL);
    Base.spinFor(forward, 2.5, rev);

    Lift.spinFor(forward, 4, rev, false);

    wait(1, sec);

    BaseLeft.spinFor(forward, 3, rev, false);
    BaseRight.spinFor(reverse, 3, rev);

    Base.spinFor(forward, 10.5, rev);
}

void driveToGoal(vex::vision::signature goalSig)
{
    while (true)
    {
        Vision.takeSnapshot(goalSig);

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        if (Vision.objects[0].exists)
        { // Check if the object exists
            if ((Vision.objects[0].centerX - tolerance) > (visCenter))
            { // Is X location of object + width > center screen then rotate counterclockwise
                rotateRight();
                Brain.Screen.print("Go Right");
            }
            else if ((Vision.objects[0].centerX + tolerance) < (visCenter))
            { // Is X location of object + width < center screen then rotate clockwise
                rotateLeft();
                Brain.Screen.print("Go Left");
            }
            else
            {
                Brain.Screen.print("Centered");
                Base.stop(brake);
                if (closeToGoal(goalSig))
                {
                    Brain.Screen.setCursor(2, 1);
                    Brain.Screen.print("Close to Goal");
                    return;
                }
                else
                {
                    driveForward();
                    wait(200, msec);
                }
            }
        }
        else
        {
            Brain.Screen.print("No Object");
        }
    }
}

bool closeToGoal(vex::vision::signature goalSig)
{ // Is the Goal close enough?
    return Vision.objects[0].width > 180;
}

void locateYGoal()
{
    driveToGoal(YGOAL);
    Base.spinFor(forward, 2.5, rev);
    locateFinshed = true;
}
void locateRGoal()
{
    driveToGoal(RGOAL);
    Base.spinFor(forward, 2.5, rev);
    locateFinshed = true;
}

void timedLocate(void (*callback)(void), int msecTime)
{
    thread findGoal(callback);
    int checkTime = Brain.timer(msec);
    curTime = Brain.timer(msec);
    while (!locateFinshed && checkTime > curTime - msecTime)
    {
        curTime = Brain.timer(msec);
        wait(20, msec);
    }
    locateFinshed = false;
    findGoal.interrupt();
}

void driveForward()
{ // Drive Forward
    Base.spin(forward, 60, pct);
}

void rotateLeft()
{ // Rotate Counterclockwise
    BaseRight.spin(forward, 20, pct);
    BaseLeft.spin(reverse, 20, pct);
}

void rotateRight()
{ // Rotate Clockwise
    BaseRight.spin(reverse, 20, pct);
    BaseLeft.spin(forward, 20, pct);
}