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

 }

 void autoRedLeft() {
   pros::lcd::print(2, "Auto:  autoRedLeft");

   // Code Here

   liftRaise(100, 1);
   driveForDistancePID(6, 100);
   rollerBackward(200);
   pros::delay(500);
   liftRaise(100, 0);
   driveForDistancePID(-6,100);
   pivotTurn(100, -90);
   driveForDistancePID(26, 200);
   pivotTurn(100, 90);
   rollerForward(200);
   driveForDistancePID(36, 200);
   rollerLock(0);
   pivotTurn(-135, 100);
   rollerForward(200);
   driveForDistancePID(32, 200);
   trayForward(50);
   pros::delay(1000);
   rollerBackward(-75);
   driveForDistancePID(-12, 50);


 }

 void autoBlueLeft() {
   pros::lcd::print(2, "Auto:  autoBlueLeft");

   // Code Here

 }

 void autoRedRight() {
   pros::lcd::print(2, "Auto:  autoRedRight");

   // Code Here

 }


 void autoBlueRight() {
    pros::lcd::print(2, "Auto:  autoBlueRight");

    // Code Here

  }
