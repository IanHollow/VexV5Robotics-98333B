#include "autonomous.h"
#include "vex.h"

int tolerance = 10;

const int visCenter = 158;
// const int visWidth = 316;

// Pre-Define Functions
void driveToGoal(signature);
void pickUpGoal();
bool closeToGoal(signature);
void driveForward();
void rotateLeft();
void rotateRight();

void fifteenSecRightLeft() {
  Base.setVelocity(100, pct);

  // Drive Forward
  Base.spinFor(forward, 2, rev, false);

  // Lift Deployment
  Lift.spinFor(forward, 4, rev);
  Lift.spinFor(reverse, 4, rev);

  driveToGoal(Vision__YGOAL);

  pickUpGoal();

  Lift.setVelocity(75, pct);
  Lift.spinFor(forward, 4, rev, false);

  wait(1, sec);

  Base.spinFor(reverse, 6, rev);
}

void fifteenSecMiddle() {
  Base.setVelocity(100, pct);

  // Drive Forward & Lift Deployment
  Base.spinFor(forward, 2, rev, false);
  Lift.spinFor(forward, 4, rev);

  BaseLeft.spinFor(forward, 0.75, rev, false);
  BaseRight.spinFor(reverse, 0.75, rev, false);
  Lift.spinFor(reverse, 4, rev);

  Base.spinFor(forward, 3.5, rev);

  driveToGoal(Vision__YGOAL);

  pickUpGoal();

  Lift.setVelocity(75, pct);
  Lift.spinFor(forward, 4, rev, false);

  wait(1, sec);

  Base.spinFor(reverse, 8, rev);
}

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
    // Set Velocity
    Base.setVelocity(100, pct);
    Lift.setVelocity(100, pct);

    fifteenSecMiddle();
    
}



void driveToGoal(signature goalSig)
{
    while (true)
    {
        Vision.takeSnapshot(goalSig);

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        if (Vision.largestObject.exists)
        { // Check if the object exists
            if ((Vision.largestObject.centerX - tolerance) > (visCenter))
            { // Is X location of object + width > center screen then rotate counterclockwise
                rotateRight();
                Brain.Screen.print("Go Right");
            }
            else if ((Vision.largestObject.centerX + tolerance) < (visCenter))
            { // Is X location of object + width < center screen then rotate clockwise
                rotateLeft();
                Brain.Screen.print("Go Left");
            }
            else
            {
              //while(true) {
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
                    wait(200, msec);
                }
              //}
            }
        }
        else
        {
            Brain.Screen.print("No Object");
        }
    }
}

void pickUpGoal()
{
    Base.setVelocity(100, pct);
    Base.spinFor(forward, 3, rev);
}

bool closeToGoal(signature goalSig)
{ // Is the Goal close enough?
    return Vision.largestObject.width > 180;
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