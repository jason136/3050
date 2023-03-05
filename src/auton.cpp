#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "flywheel.hpp"
#include "misc.hpp"
#include "file.hpp"
#include "screen.hpp"
#include "opcontrol.hpp"

extern int selection;
extern pros::Mutex mutex;
bool recAutonActive;
/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on GUI input
 **/
void recordableAuton() {
    //printVectors();
    recAutonActive = true;
    pros::Task recAutonThread(recAutonLoop);

    while (true) {}
}

void recAutonLoop(void * param) {
	std::cout << "recAutonLoop started" << std::endl;
    // char filename[20];
    // sprintf(filename, "/usd/RecAuton%i.txt", selection);
    // readFromFile(filename);

    int interations = getVectorSize();
    int recOutputs[28];
    double cords[3];
    int starttime = pros::millis();
    if (interations > 0) {
        for (int index = 0; index < interations; index++) {
            updateVecs(index, &recOutputs[0]);
            updateLocation(index, &cords[0]);

            mutex.take(25);
            // courseCorrect(index, &recOutputs[0], &cords[0]);
            processInput(&recOutputs[0]);
            mutex.give();

            pros::delay(20);
        }
    }

    std::cout << "auton run time ellapsed: " << pros::millis() - starttime << std::endl;
}

    // pros::Task thread1(closeBackClaw, (void*)500);

void autoRed1() {

    resetGyro();
    setIndexer(0);

    // drive to first roller
    driveForDistancePID(-11, 150, 1000);
    gyroTurn(90, 1000);

	setFlywheelSpeed(505);
	spinFlywheel(true);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);

    gyroTurn(7, 1500);

    // fire 2 disks
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

    gyroTurn(125, 1500);
    
    //Collect discs
    spinIntake(127);

    //Drive to center
    driveForDistancePID(-40, 75);

	setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

    gyroTurn(-92, 1500);

    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    //Stop spinning flywheel
    spinIntake(0);
    spinFlywheel(false);

}

void autoBlue1() {

    resetGyro();
    setIndexer(0);

    // drive to first roller
    driveForDistancePID(-11, 150);
    gyroTurn(-90, 1000);

	setFlywheelSpeed(505);
	spinFlywheel(true);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);

    gyroTurn(-7, 1500);

    // fire 2 disks
    // Disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

   //Disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    // Stop spinning flywheel
	spinFlywheel(false);

    //Turn; recollect discs
    gyroTurn(-125, 1500);

    //Disc collection
    spinIntake(127);

    // Drive to center
    driveForDistancePID(-40, 75);

	setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

    gyroTurn(92, 1500);

    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    //Stop spinning flywheel
    spinIntake(0);
    spinFlywheel(false);

}

void autoRed2() {
 resetGyro();
    setIndexer(0);

    // drive to first roller
    driveForDistancePID(-11, 150, 1000);
    gyroTurn(-90, 1000);

	setFlywheelSpeed(505);
	spinFlywheel(true);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);

    gyroTurn(-7, 1500);

    // fire 2 disks
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

    gyroTurn(-125, 1500);
    
    //Collect discs
    spinIntake(127);

    //Drive to center
    driveForDistancePID(-40, 75);

	setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

    gyroTurn(-92, 1500);

    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    //Stop spinning flywheel
    spinIntake(0);
    spinFlywheel(false);

 
}

void autoBlue2() {

}

void autoRed3() {

}

void autoBlue3() {

}

void skillRun() {

    resetGyro();
    setIndexer(0);

    // drive to roller1
    driveForDistancePID(-11, 150, 1000);
    gyroTurn(90, 1000);

	setFlywheelSpeed(525);
	spinFlywheel(true);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(675);
    spinIntake(0);
    driveForDistancePID(2, 150);

gyroTurn(8, 1500);

    // fire 2 disks
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	spinFlywheel(false);

    //Intake 3 disks

gyroTurn(125, 1500);

    spinIntake(127);

    driveForDistancePID(-40, 75);

	setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

gyroTurn(-92, 1500);

    pros::delay(1000);

    //fire 3 disks
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    spinIntake(0);
    spinFlywheel(false);

resetGyro();
    setIndexer(0);

gyroTurn(92, 1500);

//Startup flywheel
    setFlywheelSpeed(505);
	spinFlywheel(true);

//Intake 3 disks
    spinIntake(127);
    driveForDistancePID(-15, 75);

// drive to far side rollers 
//(continuing from the midfield position at Void autoRed1())
     driveForDistancePID(15, 75);

// Repostion to shoot
gyroTurn(-92, 1500);

// fire 3 disks
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

//Position to center row of disks
driveForDistancePID(-10, 75);
gyroTurn(92, 1500);

//Intake 3 disks
 spinIntake(127);

    driveForDistancePID(-30, 75);

	setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(500);

//Reposition to shoot
gyroTurn(-40, 1500);

// fire 3 disks
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(200);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

gyroTurn(40, 1500);

    //Intake 2 disks
    spinIntake(127);
    driveForDistancePID(-15, 75);

    //Position infront of roller
    gyroTurn(30, 1500);
    driveForDistancePID(-12, 150);
    gyroTurn(-92, 1500);
    driveForDistancePID(-12, 150);

    //Spin roller3
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);

gyroTurn(-90, 1500);
driveForDistancePID(-15, 150);
gyroTurn(-90, 1500);
driveForDistancePID(-15, 150);
gyroTurn(90, 1500);
driveForDistancePID(-15, 150);

    ////Spin roller4
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);

setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(500);

gyroTurn(-60, 1500);

    //Fire 2 disks
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    //Stop spinning flywheel
    spinFlywheel(false);

gyroTurn(115, 1500);

driveForDistancePID(-2, 75);
gyroTurn(-3, 1500);

//Intake 3 disks

gyroTurn(125, 1500);

    spinIntake(127);

    driveForDistancePID(-40, 75);

	setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

gyroTurn(-92, 1500);

    pros::delay(1000);

    //fire 3 disks
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1000);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    spinIntake(0);
    spinFlywheel(false);


    //Startup flywheel
    setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

    //Intake 3 disks
    spinIntake(127);
    driveForDistancePID(-15, 75);
     pros::delay(200);

gyroTurn(130, 1500);

    // fire 3 disks
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

gyroTurn(150, 1500);

    //Intake 3 disks
    setFlywheelSpeed(470);
	spinFlywheel(true);
    pros::delay(200);

    spinIntake(127);

    driveForDistancePID(-10, 75);

    gyroTurn(90, 1500);
    driveForDistancePID(-25, 75);

gyroTurn(130, 1500);

    //Fire 3 disks
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    setFlywheelSpeed(510);
    pros::delay(2000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

gyroTurn(-130, 1500);

    //Intake 2 disks
    spinIntake(127);

    driveForDistancePID(-20, 75);

gyroTurn (130, 1500);

    //Fire 2 disks
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    //Stop spinning flywheel
    spinFlywheel(false);

    //Spin Roller2
    driveForDistancePID(15, 75);
    gyroTurn (90, 1500);
    driveForDistancePID(-15, 75);

    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);


gyroTurn (-175, 1500);


resetGyro();
    setIndexer(0);


    setEndgame(1);
    pros::delay(200);
    setEndgame(0);
    pros::delay(200);
    setEndgame(1);
    pros::delay(200);
    setEndgame(0);
    pros::delay(200);
    setEndgame(1);
    pros::delay(200);
    setEndgame(0);
    pros::delay(200);
    setEndgame(1);
    pros::delay(200);
    setEndgame(0);

}