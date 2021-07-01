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
     std::cout << "Running Auto - autoSkills Code " << "\n";
   }

   // Old code below use only for reference. ie delete
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
   if (DEBUG_ON) {
     std::cout << "Running Auto - autoRedLeft Code " << "\n";
   }

   // Code Here

 }

 void autoBlueLeft() {
   pros::lcd::print(2, "Auto:  autoBlueLeft");
   if (DEBUG_ON) {
     std::cout << "Running Auto - autoBlueLeft Code " << "\n";
   }

   // Code Here

 }

 void autoRedRight() {
   pros::lcd::print(2, "Auto:  autoRedRight");
   if (DEBUG_ON) {
     std::cout << "Running Auto - autoRedRight Code " << "\n";
   }

   // Code Here

 }


 void autoBlueRight() {
    pros::lcd::print(2, "Auto:  autoBlueRight");
    if (DEBUG_ON) {
      std::cout << "Running Auto - autoBlueRight Code " << "\n";
    }

    // Code Here

  }
