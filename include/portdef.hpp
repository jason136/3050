#ifndef PORT_DEF_H_
#define PORT_DEF_H_

// Motor Port Assignments
// Drive Base Motors
#define FRONT_RIGHT_DRIVE_MOTOR 8
#define FRONT_LEFT_DRIVE_MOTOR 20
#define BACK_RIGHT_DRIVE_MOTOR 14
#define BACK_LEFT_DRIVE_MOTOR 16

// Tray Motor
#define TRAY_MOTOR_PORT 5

// Lift Motor
#define RIGHT_TOP_LIFT_MOTOR 3
#define RIGHT_BOTTOM_LIFT_MOTOR 4
#define LEFT_TOP_LIFT_MOTOR 1
#define LEFT_BOTTOM_LIFT_MOTOR 2

// Conveyor Motors
#define CONVEYOR_MOTOR 18

// Radio and Controllers Port Definitions
#define VEX_RADIO 21

// Vision Sensors

#define VISION_PORT 100

// Tri Port Assignments, Ports A-H are mapped to 1-8
#define PNEUMATIC_PORT_1 1
#define PNEUMATIC_PORT_2 2

// LEGACY Port Assignments

// GLOBAL DEBUGGING Variables
#define DEBUG_ON false

#define FLIP_FLOP 1

#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code

#endif
