#include "main.h"
#include "portdef.h"
#include "auto.h"
#include "chassis.h"
#include "lift.h"
#include "roller.h"
#include "tray.h"

/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on GUI input
 **/
 void skillRun() {

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
