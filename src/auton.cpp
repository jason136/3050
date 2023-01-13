#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "flywheel.hpp"
#include "module.hpp"
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
    driveForDistancePID(-14, 150, 1000);
    gyroTurn(90, 1000);

    // spin first roller
    driveForDistancePID(-2, 150);
    spinIntake(-80);
    pros::delay(500);
    spinIntake(0);
    driveForDistancePID(2, 150);
    gyroTurn(-55, 1000);

    // drive to firing spot
	setFlywheelSpeed(470);
	spinFlywheel(true);

    // driveForDistancePID(35, 200);
    driveForDistancePID(45, 175);
    // driveForDistancePID(5, 150);
    pros::delay(200);
    gyroTurn(100, 1800);

    // fire 2 disks
    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

    pros::delay(2000);

    setIndexer(0);
    pros::delay(200);
    setIndexer(1);

	spinFlywheel(false);

    // drive to second roller
    gyroTurn(92, 1500);
    driveForDistancePID(-38, 200);
    gyroTurn(-50, 1000);

    // spin second roller
    spinIntake(80);
    // driveForDistancePID(-2, 100);
    chassisMoveIndividuals(-40, -40, -40, -40);
    pros::delay(1000);
    driveForDistancePID(2, 100);
    spinIntake(0);
}

void autoBlue1() {

}

void autoRed2() {

}

void autoBlue2() {

}

void autoRed3() {

}

void autoBlue3() {

}

void skillRun() {
    
    std::cout << "running skills" << std::endl;

    calibrateGyro();
    std::cout << "calibrated" << std::endl;

    gyroTurn(-45, 1500);
    gyroTurn(90, 2000);


    // gyroTurn(360, 4000000);

    // gyroTurn(90, 1000);
    // pros::delay(1000);
    // gyroTurn(180, 1000);
    // pros::delay(1000);
    // gyroTurn(270, 1000);
    // pros::delay(1000);
    // gyroTurn(360, 1000);

    // driveForDistancePID(12, 200);
    // driveForDistancePID(-12, 200);

}

void courseCorrect(int index, int * recOutputs, double * cords) {
    double futureCords[3];
    double currentCords[3];
    
    if (index + 10 < getVectorSize()) {
        updateLocation(index + 10, &futureCords[0]);
        trackSpeed(&currentCords[0]);

        if (fabs(currentCords[0]) < fabs(futureCords[0]) - 10) {
            recOutputs[1] *= 1.05;
        }
        else if (fabs(currentCords[0]) > fabs(futureCords[0] + 10)) {
            recOutputs[1] *= 0.95;
        }
        
        if (fabs(currentCords[1]) < fabs(futureCords[1] - 10)) {
            recOutputs[3] *= 1.05;
        }
        else if (fabs(currentCords[1]) > fabs(futureCords[1] + 10)) {
            recOutputs[3] *= 0.95;
        }
    }
}