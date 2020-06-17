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


 void skillRun() {
   pros::lcd::print(2, "Auto: autoSkills");
   if (DEBUG_ON) {
     std::cout << "Running Auto - SkillRun Code " << "\n";
   }

   // Code Here
   liftSetZero(0);
   liftRaise(100, 2);
   liftRaise(100, 1);
   liftRaise(100, 2);
   liftRaise(100, 1);
   liftRaiseManual(100);
   pros::delay(100);
   liftRaiseManual(-100);
   pros::delay(100);
   liftRaiseManual(100);
   pros::delay(100);
   liftRaiseManual(-100);
   pros::delay(100);
   liftLock();
   liftSetZero(0);

   setIndividualMotor(100, -100, -100, 100);
   pros::delay(2000);
   chassisStopDrive();
 }

 void autoRedLeft() {
   pros::lcd::print(2, "Auto:  autoRedLeft");

   liftSetZero(0);
   liftRaise(100, 2);
   liftRaise(100, 1);
   liftRaise(100, 2);
   liftRaise(100, 1);
   liftRaiseManual(100);
   pros::delay(100);
   liftRaiseManual(-100);
   pros::delay(100);
   liftRaiseManual(100);
   pros::delay(100);
   liftRaiseManual(-100);
   pros::delay(100);
   liftLock();
   liftSetZero(0);

   setIndividualMotor(100, -100, -100, 100);
   pros::delay(1000);
   chassisStopDrive();
   setIndividualMotor(-100, 100, 100, -100);
   pros::delay(500);
   chassisStopDrive();

 }

 void autoBlueLeft() {
   pros::lcd::print(2, "Auto:  autoBlueLeft");

   // Code Here

   liftSetZero(0);
   liftRaise(100, 2);
   liftRaise(100, 1);
   liftRaise(100, 2);
   liftRaise(100, 1);
   liftRaiseManual(100);
   pros::delay(100);
   liftRaiseManual(-100);
   pros::delay(100);
   liftRaiseManual(100);
   pros::delay(100);
   liftRaiseManual(-100);
   pros::delay(100);
   liftLock();
   liftSetZero(0);

   setIndividualMotor(-100, 100, 100, -100);
   pros::delay(1000);
   chassisStopDrive();;
   setIndividualMotor(100, -100, -100, 100);
   pros::delay(500);
   chassisStopDrive();

 }

 /*
 liftSetZero(0);
 liftRaise(100, 2);
 liftRaise(100, 1);
 liftRaise(100, 2);
 liftRaise(100, 1);
 liftRaiseManual(100);
 pros::delay(100);
 liftRaiseManual(-100);
 pros::delay(100);
 liftRaiseManual(100);
 pros::delay(100);
 liftRaiseManual(-100);
 pros::delay(100);
 liftLock();
 liftSetZero(0);
 pros::delay(100);
 rollerForward(200);
 driveForDistancePID(24, 100);
 rollerStop(0);
 driveForDistancePID(-24, -100);
 pivotTurn(90, 90);
 driveForDistancePID(15, 100);
 rollerBackward(-200);
 pros::delay(2500);
 driveForDistancePID(-5, -90);

 */

 void autoRedRight() {
   pros::lcd::print(2, "Auto:  autoRedRight");

   // Code Here
   liftRaiseForEncoder(20, 295);
   driveForDistancePID(32, 145);
   liftRaiseForEncoder(-30, 250);
   rollerBackward(-200);

   rollerStop(0);
    driveForDistancePID(-5, -35);
    liftRaiseForEncoder(-50, 0);
    rollerForward(200);
    driveForDistancePID(-4, -145);
    driveForDistancePID(4, 145);
    rollerStop(0);
    driveForDistancePID(-32, -165);
    pivotTurn(100, 90);
    driveForDistancePID(30, 120);
    rollerBackward(-200);
    driveForDistancePID(-5, -200);
    rollerStop(0);

 }


 void autoBlueRight() {
    pros::lcd::print(2, "Auto:  autoBlueRight");

    // Code Here

  }
