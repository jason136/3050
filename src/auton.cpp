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
    setIndexer(1);

    // drive to first roller
    driveForDistancePID(-15, 150, 1000);
    gyroTurn(90, 1000);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-20, -20, -20, -20);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);
    gyroTurn(-55, 1000);

    // drive to firing spot
	setFlywheelSpeed(470);
	spinFlywheel(true);

    // driveForDistancePID(35, 200);
    driveForDistancePID(44, 175);
    // driveForDistancePID(5, 150);
    pros::delay(200);
    gyroTurn(105, 1800);

    // fire 2 disks
    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

    pros::delay(2000);

    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

	spinFlywheel(false);

    // tested code ends here, end here for just roller + 2 shots

    // drive to second roller

    // gyroTurn(92, 1500);
    gyroTurn(-103, 1800);

    // driveForDistancePID(-38, 200);
    driveForDistancePID(35, 200);

    // gyroTurn(-50, 1000);
    gyroTurn(130, 1000);

    // spin second roller
    spinIntake(80);
    // driveForDistancePID(-2, 100);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(1000);
    driveForDistancePID(1, 100);
    spinIntake(0);
    chassisStopDrive(pros::E_MOTOR_BRAKE_HOLD);
}

void autoBlue1() {

    resetGyro();
    setIndexer(1);

    // drive to first roller
    driveForDistancePID(-15, 150, 1000);
    gyroTurn(-90, 1000);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-20, -20, -20, -20);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);
    gyroTurn(55, 1000);

    // drive to firing spot
	setFlywheelSpeed(470);
	spinFlywheel(true);

    // driveForDistancePID(35, 200);
    driveForDistancePID(44, 175);
    // driveForDistancePID(5, 150);
    pros::delay(200);
    gyroTurn(-105, 1800);

    // fire 2 disks
    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

    pros::delay(2000);

    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

	spinFlywheel(false);

    // tested code ends here, end here for just roller + 2 shots

    // drive to second roller

    // gyroTurn(-92, 1500);
    gyroTurn(103, 1800);

    // driveForDistancePID(-38, 200);
    driveForDistancePID(35, 200);

    // gyroTurn(50, 1000);
    gyroTurn(-130, 1000);

    // spin second roller
    spinIntake(80);
    // driveForDistancePID(-2, 100);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(1000);
    driveForDistancePID(1, 100);
    spinIntake(0);
    chassisStopDrive(pros::E_MOTOR_BRAKE_HOLD);
}

void autoRed2() {

    resetGyro();
    setIndexer(1);

    // drive to first roller
    driveForDistancePID(-15, 150, 1000);
    gyroTurn(90, 1000);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-20, -20, -20, -20);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);
    gyroTurn(-55, 1000);

    // drive to firing spot
	setFlywheelSpeed(470);
	spinFlywheel(true);

    // driveForDistancePID(35, 200);
    driveForDistancePID(44, 175);
    // driveForDistancePID(5, 150);
    pros::delay(200);
    gyroTurn(105, 1800);

    // fire 2 disks
    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

    pros::delay(2000);

    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

	spinFlywheel(false);
}

void autoBlue2() {

    resetGyro();
    setIndexer(1);

    // drive to first roller
    driveForDistancePID(-15, 150, 1000);
    gyroTurn(-90, 1000);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    chassisMoveIndividuals(-20, -20, -20, -20);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);
    gyroTurn(55, 1000);

    // drive to firing spot
	setFlywheelSpeed(470);
	spinFlywheel(true);

    // driveForDistancePID(35, 200);
    driveForDistancePID(44, 175);
    // driveForDistancePID(5, 150);
    pros::delay(200);
    gyroTurn(-105, 1800);

    // fire 2 disks
    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

    pros::delay(2000);

    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

	spinFlywheel(false);
}

void autoRed3() {

}

void autoBlue3() {

}

void skillRun() {

    seek(0, 0, 10000);

}