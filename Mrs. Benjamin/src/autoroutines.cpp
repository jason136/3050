#include "main.h"
#include "portdef.h"
#include "auto.h"
#include "chassis.h"
#include "lift.h"
#include "roller.h"
#include "tray.h"

/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on LCD input
 **/


 void lunarEclipse() {
   pros::lcd::print(3, "Auto: LUNAR ECLIPSE");
   if (DEBUG_ON) {
     std::cout << "Running Auto - SkillRun Code " << "\n";
   }

   // Code Here

 }

 void newMoon() {
   pros::lcd::print(3, "Auto:  New Moon");

   // Code here

   driveForDistancePID(3, 100);
   pivotTurn(100, 92);
   // Forward 3 inches, turn 92 degrees right
   pros::delay(200);
   driveForDistancePID(24, 150);
   driveForDistancePID(-10, 150);
   // Wait, go forward 24 inches, back up 10 inches
   // 1 Point
   // TURNS RIGHT

 }

 void waxingGibbous() {
   pros::lcd::print(3, "Auto:  Waxing Gibbous");

   // Code here

   driveForDistancePID(3, 100);
   pivotTurn(100, -92);
   // Forward 3 inches, turn 92 degrees left
   pros::delay(200);
   driveForDistancePID(24, 150);
   driveForDistancePID(-10, 150);
   // Wait, go forward 24 inches, back up 10 inches
   // 1 Point
   // TURNS LEFT

 }

 void waningGibbous() {
   pros::lcd::print(3, "Auto:  Waning Gibbous");

   // Code Here

   liftRaiseManual(-100);
   pros::delay(800);
   liftRaiseManual(100);
   pros::delay(800);
   liftLock();
   // Lift the lift up and down -purpose is to deploy the tray
   rollerForward(200);
   driveForDistancePID(36, 85);
   pros::delay(200);
   // drive forward while intaking
   pivotTurn(100, 140);
   driveForDistancePID(32, 100);
   // turn and drive forward to the zone
   trayForward(30);
   rollerBackward(25);
   pros::delay(400);
   rollerStop();
   pros::delay(1500);
   // tilt the tray and outtake the rollers
   driveForDistancePID(-10, 200);
   rollerForward(0);
   // drive backward and stop the roller
   // 5 points on unsafe zone
   // 1 cube preload with 4 cube intake
   // TURNS RIGHT

 }

 /*
INVERSE OF ABOVE:
liftRaiseManual(-100);
pros::delay(800);
liftRaiseManual(100);
pros::delay(800);
liftLock();
// Lift the lift up and down -purpose is to deploy the tray
rollerForward(200);
driveForDistancePID(36, 85);
pros::delay(200);
// drive forward while intaking
pivotTurn(100, 140);
driveForDistancePID(32, 100);
// turn and drive forward to the zone
trayForward(30);
rollerBackward(25);
pros::delay(400);
rollerStop();
pros::delay(1500);
// tilt the tray and outtake the rollers
driveForDistancePID(-10, 200);
rollerForward(0);
// drive backward and stop the roller
// 4 points on unsafe zone
// 1 cube preload with 4 cube intake
// TURNS LEFT
 */


 void fullMoon() {
    pros::lcd::print(3, "Auto:  Full Moon");

    // Code Here

    //Skills for meow

    liftRaiseManual(-100);
    pros::delay(800);
    liftRaiseManual(100);
    pros::delay(800);
    liftLock();
    // Lift the lift up and down -purpose is to deploy the tray
    rollerForward(200);
    driveForDistancePID(36, 85);
    // Intake the cube, drive 3 ft forwards
    setIndividualMotor(85, 65);
    pros::delay(500);
    setIndividualMotor(65, 85);
    pros::delay(500);
    // Swerves around tower, returns to original vector
    driveForDistancePID(36, 85);
    pivotTurn(100, 90);
    driveForDistancePID(24, 85);
    // go forward 36 in, turn right 90 degrees, drive 24 in forward
    trayForward(30);
    rollerBackward(25);
    pros::delay(400);
    rollerForward(0);
    pros::delay(1500);
    // place stack, reset intake, drive backwards 24 in
    driveForDistancePID(-24, 100);
    pivotTurn(100, 90);
    rollerForward(100);
    driveForDistancePID(45, 100);
    liftRaise(1, 100);
    rollerBackward(100);
    pros::delay(750);
    driveForDistancePID(-36, 100);
    liftRaise(0, 100);
    liftSetZero();
    pivotTurn(90, 100);
    rollerForward(100);
    driveForDistancePID(25, 100);
    rollerForward(0);
    liftRaise(1, 100);
    rollerBackward(100);
    pros::delay(750);
    rollerForward(0);
    driveForDistancePID(12, 100);
    liftRaise(0, 100);
    pivotTurn(-90, 100);
    rollerForward(100);
    driveForDistancePID(112, 85);
    rollerForward(0);
    pivotTurn(-90, 100);
    driveForDistancePID(38, 100);
    trayForward(30);
    rollerBackward(25);
    pros::delay(400);
    rollerForward(0);
    pros::delay(1500);
    driveForDistancePID(-12, 100);
  }

  // u cute thx

  // Old Autonomous Routines, including encoder testing

  /*
  This script is supposed to make the robot drive forward 1 foot, drive
  backward 1 foot, spin 180 degrees clockwise and then spin 180 degress ccw

  driveForDistancePID(12, 100);
  driveForDistancePID(-12, 100);

  pivotTurn(200, 180);
  pivotTurn(200, -180);

  */

  /*
  This is supposed to make the robot drive in a circle at full power
  Post testing note: Running motors at full power increases unreliability,
  especially in turns. Consider running at 0.5 or 0.75 times power.

  driveForDistancePID(12, 200);
  pros::delay(100);
  pivotTurn(-90, 200);
  driveForDistancePID(12, 200);
  pros::delay(100);
  pivotTurn(-90, 200);
  driveForDistancePID(12, 200);
  pros::delay(100);
  pivotTurn(-90, 200);
  driveForDistancePID(12, 200);
  pros::delay(100);
  pivotTurn(-90, 200);
  */

  /*
  This script is supposed to make the robot's lift move to the highest point,
  move to the lowest point, move to the short tower's height, and return to
  the base get_position

  liftSetZero();
  liftRaise(100, 2);
  liftRaise(100, 0);
  liftRaise(100, 1);
  liftRaise(100, 0);

  */

  /*
  This auton routine shakes the robot and shakes the arms while the rollers are
  in full power in reverse. The goal of this is to hopefully deploy the robot's
  tray without any human interaction or love...
  Note: This is just a temporary solution, we are still working on the tray
  mechanism to make the deploy smoother so he can have emotions.

  rollerBackward(100);               // Set the roller to full power in reverse
  liftRaiseManual(200);              // Raise the lift at full power
  pros::delay(200);                  // Give time for the lift to move
  liftRaiseManual(-200);             // Lower the Raise at full power
  pros::delay(200);
  driveForDistancePID(3, 200);       // Drive the robot forward 3 inches
  driveForDistancePID(-3, 200);      // Drive the robot backward 3 inches
  driveForDistancePID(3, 200);       // Repeat 3 times, goal is a violent shake
  driveForDistancePID(-3, 200);
  driveForDistancePID(3, 200);
  driveForDistancePID(-3, 200);

  */

  /*
  Prototype Code Deemed Obsolete on 3/4/2020

  trayForward(80);
  rollerBackward(100);
  pros::delay(400);
  liftRaiseManual(100);
  pros::delay(200);
  trayBackward(80);
  pros::delay(400);
  liftRaiseManual(-100);
  pros::delay(200);
  liftLock();
  trayLock();
  rollerForward(200);
  driveForDistancePID(36, 100);
  pros::delay(100);
  pivotTurn(-135, 100);
  driveForDistancePID(30, 100);
  pivotTurn(-10, 100);
  driveForDistancePID(20, 100);
  rollerBackward(50);
  trayForward(80);
  pros::delay(3000);
  driveForDistancePID(-5, 50);
  */


// Jason is the most dominant
// all praise the lord and saviaor Jason
// Thank you for your hard work
// Alex is pretty great too

// Naw Dan is the absolute Fire
// Dan is the ULTIMATE CARRY
// I can't fathom where we would be without Dan
// Thank you Dan for choosing 3050C
// We are glad to have you
