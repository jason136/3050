#include "main.hpp"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "lift.hpp"
#include "roller.hpp"

/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on GUI input
 **/
 void skillRun() {

   // Old code below use only for reference. ie delete
   liftMove(100);
   pros::delay(100);
   liftMove(-100);
   pros::delay(100);
   liftMove(100);
   pros::delay(100);
   liftMove(-100);
   pros::delay(100);
   liftLock();

   setIndividualMotor(100, -100, -100, 100);
   pros::delay(2000);
   chassisStopDrive();
 }

 void autoRedLeft() {

   // Code Here

 }

 void autoBlueLeft() {

   // Code Here

 }

 void autoRedRight() {

   // Code Here

 }


 void autoBlueRight() {

    // Code Here penis

  }
