#include "autonomous.h"
#include "visionCalibration.h"
#include "vex.h"

int tolerance = 10;

const int visCenter = 158;
// const int visWidth = 316;

unsigned int curTime = Brain.timer(msec);
bool locateFinshed = false;

// Pre-Define Functions
void driveToGoal(signature);
bool closeToGoal(signature);
void driveForward();
void rotateLeft();
void rotateRight();
void locateGoal() {
  driveToGoal(YGOAL);
  Base.spinFor(forward, 2.5, rev);
  locateFinshed = true;
}

void sec15RL() {
  Base.setVelocity(100, pct);

  // Drive Forward
  Base.spinFor(forward, 2.75, rev, false);

  // Lift Deployment
  Lift.spinFor(forward, 4, rev);
  Lift.spinFor(reverse, 4, rev);

  thread findGoal(locateGoal);

  unsigned int checkTime = Brain.timer(msec);
  curTime = Brain.timer(msec);

  while(!locateFinshed && checkTime > curTime - 5000) {
    curTime = Brain.timer(msec);
    wait(20, msec);
  }

  findGoal.interrupt();

  Lift.setVelocity(75, pct);
  Lift.spinFor(forward, 4, rev, false);

  wait(1, sec);

  Base.spinFor(reverse, locateFinshed ? 5.5 : 8, rev, false);

  wait(1, sec);

  Lift.setVelocity(100, pct);
  Lift.spinFor(reverse, 4, rev);
}

void sec15MfrmL() {
  Base.setVelocity(100, pct);

  // Drive Forward & Lift Deployment
  Base.spinFor(forward, 2, rev, false);
  Lift.spinFor(forward, 4, rev);

  BaseLeft.spinFor(forward, 0.75, rev, false);
  BaseRight.spinFor(reverse, 0.75, rev, false);
  Lift.spinFor(reverse, 4, rev);

  Base.spinFor(forward, 3.5, rev);

  driveToGoal(YGOAL);

  Lift.setVelocity(75, pct);
  Lift.spinFor(forward, 4, rev, false);

  wait(1, sec);

  Base.spinFor(reverse, 8, rev);
}

void sec15MfrmR() {
  Base.setVelocity(100, pct);

  // Drive Forward & Lift Deployment
  Base.spinFor(forward, 2, rev, false);
  Lift.spinFor(forward, 4, rev);

  BaseLeft.spinFor(reverse, 0.75, rev, false);
  BaseRight.spinFor(forward, 0.75, rev, false);
  Lift.spinFor(reverse, 4, rev);

  Base.spinFor(forward, 3.5, rev);

  driveToGoal(YGOAL);

  Lift.setVelocity(75, pct);
  Lift.spinFor(forward, 4, rev, false);

  wait(1, sec);

  Base.spinFor(reverse, 8, rev);
}

void autoSkills() {
  Base.setVelocity(100, pct);
  Lift.setVelocity(100, pct);

  // Drive Forward
  Base.spinFor(forward, 10, rev);

  Base.spinFor(reverse, 1, rev);
  
  BaseLeft.spinFor(reverse, 2.3, rev, false);
  BaseRight.spinFor(forward, 2.3, rev);

  driveToGoal(YGOAL);

  Base.spinFor(forward, 8, rev);

  Base.spinFor(reverse, 2, rev);

  BaseLeft.spinFor(forward, 1.5, rev, false);
  BaseRight.spinFor(reverse, 1.5, rev);

  Base.spinFor(reverse, 1, rev);

  driveToGoal(YGOAL);

  Base.spinFor(forward, 6, rev);

  Base.spinFor(reverse, 1, rev);

  BaseLeft.spinFor(reverse, 1.5, rev, false);
  BaseRight.spinFor(forward, 1.5, rev);

  Base.spinFor(forward, 5, rev);
  BaseRight.spinFor(forward, 1.75, rev);
  Base.spinFor(forward, 0.5, rev);

  Base.spinFor(reverse, 1.5, rev);

  BaseLeft.spinFor(forward, 2.65, rev, false);
  BaseRight.spinFor(reverse, 2.65, rev);

  Base.spinFor(reverse, 1, rev);

  Lift.spinFor(forward, 4, rev, false);
  Base.spinFor(forward, 2, rev);
  Lift.spinFor(reverse, 4, rev, false);

  driveToGoal(RGOAL);
  Base.spinFor(forward, 2.5, rev);

  Lift.spinFor(forward, 4, rev, false);

  wait(1, sec);

  Base.spinFor(reverse, 10, rev);
}

// Main Function: Called at Start of Autonomous
void autonomousStart()
{
    // Set Velocity
    Base.setVelocity(100, pct);
    Lift.setVelocity(100, pct);
    
    sec15RL();
}



void driveToGoal(signature goalSig)
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
              //while(true) {
                Brain.Screen.print("Centered");
                Base.stop(brake);
                if (closeToGoal(goalSig))
                {
                    Brain.Screen.setCursor(2, 1);
                    Brain.Screen.print("Close to Goal");
                    Base.stop(coast);
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

bool closeToGoal(signature goalSig)
{ // Is the Goal close enough?
    return Vision.objects[0].width > 180;
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