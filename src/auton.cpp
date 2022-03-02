#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "lift.hpp"
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
    char filename[20];
    sprintf(filename, "/usd/RecAuton%i.txt", selection);
    readFromFile(filename);

    int interations = getVectorSize();
    int recOutputs[28];

    double cords[3];
    int starttime = pros::millis();
    if (interations > 0) {
        for (int index = 0; index < interations; index++) {
            updateVecs(index, &recOutputs[0]);
            updateLocation(index, &cords[0]);

            mutex.take(25);
            courseCorrect(index, &recOutputs[0], &cords[0]);

            // std::cout << recOutputs[0] << recOutputs[1] << recOutputs[2] << recOutputs[3] << std::endl;
            // std::cout << " rec: " << recOutputs[5] << std::endl;
            
            processInput(&recOutputs[0]);
            mutex.give();


            // if (recAutonActive) {
            // }

            //std::cout << "selection: " << selection << " execute line " << x << "of" << interations << std::endl;
            pros::delay(20);
        }
    }

    std::cout << "auton run time ellapsed: " << pros::millis() - starttime << std::endl;
}

extern pros::Imu intertialSensor(INERTIAL_PORT);

void autoRed1() {

    intertialSensor.set_rotation(0);

    driveForDistancePID(12, 200);
    toggleLiftClawPneumatics(1);
    driveForDistancePID(-12, 200);

    gyroTurn(90, 500);
    pros::Task closeClawThread(closeBackClaw, (void*)500);
    driveForDistancePID(-4, 200);
    driveForDistancePID(24, 200);

    gyroTurn(180, 500);
    driveForDistancePID(-72, 200);
    toggleBackClawPneumatics(1);
    spinRollerForEncoder(1000, 200);
    pros::Task closeClawThread(closeBackClaw, (void*)1000);
    driveForDistancePID(12, 50);

    gyroTurn(90, 500);
    visPathfind(3, 2000);
    toggleLiftClawPneumatics(1);
    gyroTurn(90, 100);
    driveForDistancePID(-24, 200);

}

void autoBlue1() {

    intertialSensor.set_rotation(0);

    visPathfind(3, 2000);
    toggleLiftClawPneumatics(1);
    pros::Task closeClawThread(closeLiftClaw, (void*)200);
    driveForDistancePID(-48, 200);
    gyroTurn(45, 100);

    visPathfind(3, 1500);
    toggleLiftClawPneumatics(1);
    pros::Task closeClawThread(closeLiftClaw, (void*)500);
    driveForDistancePID(-60, 200);

    gyroTurn(90, 500);
    driveForDistancePID(-48, 200);
    toggleBackClawPneumatics(1);
    spinRollerForEncoder(1000, 200);
    pros::Task closeClawThread(closeBackClaw, (void*)1000);
    driveForDistancePID(12, 50);

}

void autoRed2() {

    intertialSensor.set_rotation(0);

    visPathfind(3, 2000);
    toggleLiftClawPneumatics(1);
    driveForDistancePID(-72, 200);

    gyroTurn(90, 500);
    driveForDistancePID(-24, 50);
    toggleBackClawPneumatics(1);
    spinRollerForEncoder(1000, 200);
    driveForDistancePID(12, 50);

}

void autoBlue2() {

    // test methods
    intertialSensor.set_rotation(0);

    visPathfind(3, 2000);
    toggleLiftClawPneumatics(1);
    driveForDistancePID(-72, 200);

    gyroTurn(90, 500);
    driveForDistancePID

}

void autoRed3() {

    // Code Here
}

void autoBlue3() {


    // Code Here
}

void skillRun() {

    // // Old code below use only for reference. ie delete
    // //liftMove(100);
    // pros::delay(100);
    // //liftMove(-100);
    // pros::delay(100);
    // //liftMove(100);
    // pros::delay(100);
    // //liftMove(-100);
    // pros::delay(100);
    // //liftLock();

    // setIndividualMotor(100, -100, -100, 100);
    // pros::delay(2000);
    // chassisStopDrive();

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