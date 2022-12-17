#include "api.h"
#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "flywheel.hpp"
#include "screen.hpp"
#include "file.hpp"
#include "module.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    // Motor Setup
    // GEARSET_36 -- RED
    // GEARSET_18 -- GREEN (default)
    // GEARSET_6 -- BLUE

    generateDatastructures();
    drawScreen();

    initializeVision();

    // initializeGps(-1.5, -1.14, 90, .223, -.223);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

bool screenInit;
extern int selection;
extern bool recAuton;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    // We are calling a autonomous function based on the selection
    // we made on the LCD

    if (!screenInit) {
        recAuton = DEFAULT_RECAUTON;
        selection = DEFAULT_SELECTION;
    }
    if (recAuton) recordableAuton();
    else {
        switch (selection) {
        case 0:
            autoRed1();
            break;
        case 1:
            autoBlue1();
            break;
        case 2:
            autoRed2();
            break;
        case 3:
            autoBlue2();
            break;
        case 4:
            autoRed3();
            break;
        case 5:
            autoBlue3();
            break;
        case 6: 
            skillRun();
            break;
        default:
            break;
        }
    }
}