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
    driveForDistancePID(-10, 120);
    gyroTurn(90, 1000);

	setFlywheelSpeed(505);
	spinFlywheel(true);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(500);
    spinIntake(0);

    driveForDistancePID(3, 150);

    pros::delay(200);
    gyroTurn(5.8, 1300);

    // fire 1 disk
    //Fire disc 1
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	// setFlywheelSpeed(505);
    pros::delay(1200);

    //Fire disc 2
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    pros::delay(1200);

    //Fire disc 3(bandaid)
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

    gyroTurn(124, 1300);

    pros::delay(200);
    
    //Collect discs
    spinIntake(200);

    //Drive to center
    driveForDistancePID(-40, 90);

    gyroTurn(-88.5, 1200);

    pros::delay(1000);

	setFlywheelSpeed(467);
	spinFlywheel(true);

    pros::delay(1000);
    
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

    pros::delay(1000);

    //Fire disc 3(bandaid)
    setIndexer(1);
    pros::delay(200);
    setIndexer(0);

    //Stop spinning flywheel
    spinIntake(0);
    spinFlywheel(false);

}

void autoBlue1() {

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

    gyroTurn(-10, 1500);

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
    spinIntake(200);

    //Drive to center
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

void autoBlue2() {
  resetGyro();
    setIndexer(0);

    // drive to first roller
    driveForDistancePID(-11, 150);
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

    gyroTurn(10, 1500);

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
    gyroTurn(125, 1500);

    //Disc collection
    spinIntake(127);

    // Drive to center
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

void autoRed3() {

    seek(1200, -600, 2000, false);

}

void autoBlue3() {

}

void skillRun() {

    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(750);
    spinIntake(0);
    driveForDistancePID(3, 150);

	setFlywheelSpeed(462);
    spinFlywheel(true);

    gyroTurn(86, 1500);

    //Fire disk 1 (shot 1)
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay (1000);

    //Fire bandaid
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay (1000);

	//Stop spinning flywheel
    spinFlywheel(false);

    gyroTurn(90, 1500);
    pros::delay(200);

    spinIntake(150);
    driveForDistancePID(-8, 50);
    pros::delay(200);
    driveForDistancePID(2, 50);
    pros::delay(200);
    driveForDistancePID(-13, 25);
    pros::delay(200);
    driveForDistancePID(12, 60);

    gyroTurn(-97, 1500);

    // COPIED FROM REDAUTO1

    // spin first roller
    driveForDistancePID(-10, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(750);
    spinIntake(0);
    driveForDistancePID(2, 150);

	setFlywheelSpeed(475);
	spinFlywheel(true);

    gyroTurn(-100, 1500);

    // fire 3 disks (Shot 2)
    //Fire disc 1
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire bandaid
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

    driveForDistancePID(6, 75);
    pros::delay(200);
    gyroTurn(-151, 1500);
    
    //Collect discs
    spinIntake(200);

    //Drive to center
    driveForDistancePID(-40, 75);

	setFlywheelSpeed(455);
	spinFlywheel(true);
    pros::delay(200);

    gyroTurn(89, 1500);

    //Fire disc 1(Shot 3)
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Bandaid Shot
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    //Stop spinning flywheel
    spinIntake(0);
    spinFlywheel(false);

    // END COPIED BIT

// gyroTurn(-95, 1500);
seek(1200, -600, 4000, false);

//Startup flywheel
    // setFlywheelSpeed(505);
	spinFlywheel(false);

    spinIntake(150);
    driveForDistancePID(-14, 50);
    pros::delay(200);
    driveForDistancePID(2, 50);
    pros::delay(200);
    driveForDistancePID(-23, 40);
    pros::delay(200);

// drive to far side rollers 
//(continuing from the midfield position at Void autoRed1())
    // driveForDistancePID(-20, 75);

    gyroTurn(-45, 1000);
    driveForDistancePID(-4, 75);

////////////////////////////////////////////////////////////////////COPIED IS BELOW

    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(750);
    spinIntake(0);
    driveForDistancePID(3, 150);

	setFlywheelSpeed(462);
    spinFlywheel(true);

    gyroTurn(86, 1500);

    //Fire disk 1 (shot 1)
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay (1000);

    //Fire bandaid
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay (1000);

	//Stop spinning flywheel
    spinFlywheel(false);

    gyroTurn(90, 1500);
    pros::delay(200);

    spinIntake(150);
    driveForDistancePID(-8, 50);
    pros::delay(200);
    driveForDistancePID(2, 50);
    pros::delay(200);
    driveForDistancePID(-13, 25);
    pros::delay(200);
    driveForDistancePID(12, 60);

    gyroTurn(-97, 1500);

    // COPIED FROM REDAUTO1

    // spin first roller
    driveForDistancePID(-10, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(750);
    spinIntake(0);
    driveForDistancePID(2, 150);

	setFlywheelSpeed(475);
	spinFlywheel(true);

    gyroTurn(-100, 1500);

    // fire 3 disks (Shot 2)
    //Fire disc 1
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire bandaid
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

	//Stop spinning flywheel
    spinFlywheel(false);

    driveForDistancePID(6, 75);
    pros::delay(200);
    gyroTurn(-151, 1500);
    
    //Collect discs
    spinIntake(200);

    //Drive to center
    driveForDistancePID(-40, 75);

	setFlywheelSpeed(455);
	spinFlywheel(true);
    pros::delay(200);

    gyroTurn(89, 1500);

    //Fire disc 1(Shot 3)
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 2
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Fire disc 3
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    pros::delay(1000);

    //Bandaid Shot
    setIndexer(1);
    pros::delay(500);
    setIndexer(0);

    //Stop spinning flywheel
    spinIntake(0);
    spinFlywheel(false);

    // END COPIED BIT

// gyroTurn(-95, 1500);
seek(-1200, 600, 4000, false);

//Startup flywheel
    // setFlywheelSpeed(505);
	spinFlywheel(false);

    spinIntake(150);
    driveForDistancePID(-14, 50);
    pros::delay(200);
    driveForDistancePID(2, 50);
    pros::delay(200);
    driveForDistancePID(-23, 40);
    pros::delay(200);


//     setEndgame(1);
//     pros::delay(200);
//     setEndgame(0);
//     pros::delay(200);
//     setEndgame(1);
//     pros::delay(200);
//     setEndgame(0);
//     pros::delay(200);
//     setEndgame(1);
//     pros::delay(200);
//     setEndgame(0);
//     pros::delay(200);
//     setEndgame(1);
//     pros::delay(200);
//     setEndgame(0);

}