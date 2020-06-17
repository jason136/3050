#include "main.h"
#include "portdef.h"
#include "auto.h"
#include "chassis.h"
#include "lift.h"
#include "shooter.h"
#include "claw.h"
#include "intake.h"


/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on LCD input
 **/


 void skillRun() {
   pros::lcd::print(2, "Auto:  skillRun");
   if(DEBUG_ON) {
     std::cout << "Running Auto - SkillRun Code " << "\n";
   }
   //shoot target and flip flag
   shootBall(300);
   pivotTurn(20, -10);
   driveForDistancePID(-45, 100);
   driveForDistancePID(20, 100);
   pivotTurn(30, 78);
   driveForDistancePID(-2, 100);
   pivotTurn(30, 158);
   //flip cap over using claw and lift
   setClawPosition();
   flipClaw(200);
   setClawPosition();
   flipClaw(200);
   driveForDistancePID(-5, 100);
   driveForDistancePID(15, 100);
   liftRaise(100, 1);
   liftLock();
   setClawPosition();
   flipClaw(200);
   liftRaise(100,0);
   driveForDistancePID(-10, 50);
   // climb back on platform
   pivotTurn(30, -79);
   driveForDistancePID(-50, 100);
   pivotTurn(30, -81);
   driveForDistancePID(-70, 150);




 };




 void autoRedLeft() {
   pros::lcd::print(2, "Auto:  autoRedLeft");
   // shoots ball, runs over bottom flag with intake, knocks cap, climbs on platform
   shootBall(300);
   pivotTurn(20, -10);
   intakeForward(100);
   driveForDistancePID(-45, 100);
   intakeStop(0);
   driveForDistancePID(45, 100);
   pivotTurn(30, 78);
   driveForDistancePID(-35, 100);
   driveForDistancePID(37, 100);
   pivotTurn(30, -81);
   driveForDistancePID(22, 100);
   pivotTurn(30, 82);
   //driveForDistancePID(10, 50);
   driveForDistancePID(-70, 150);

 };

 void autoBlueLeft() {
   pros::lcd::print(2, "Auto:  autoBlueLeft");

   //how to use claw + lift autonomously
   driveForDistancePID(10, 100);
   liftRaise(100, 1);
   liftLock();
   setClawPosition();
   flipClaw(200);
   liftRaise(100,0);
   driveForDistancePID(-10, 50);



 };

 void autoRedRight() {
   pros::lcd::print(2, "Auto:  autoRedRight");

 };

 void autoBlueRight() {
   pros::lcd::print(2, "Auto:  autoBlueRight");
   //does same as autoRedLeft
   shootBall(300);
   intakeForward(100);
   driveForDistancePID(-45, 100);
   intakeStop(0);
   driveForDistancePID(45, 100);
   pivotTurn(30, -75);
   driveForDistancePID(-35, 100);
   driveForDistancePID(37, 100);
   pivotTurn(30, 81);
   driveForDistancePID(20, 100);
   pivotTurn(30, -81);
   //driveForDistancePID(10, 50);
   driveForDistancePID(-70, 150);


 };
