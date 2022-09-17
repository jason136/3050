#ifndef PORT_DEF_H_
#define PORT_DEF_H_

// Motor Port Assignments
// Drive Base Motors
#define FRONT_RIGHT_DRIVE_MOTOR 17
#define FRONT_LEFT_DRIVE_MOTOR 18
#define BACK_RIGHT_DRIVE_MOTOR 19
#define BACK_LEFT_DRIVE_MOTOR 20

// Lift Motor
#define FLYWHEEL_1 3
#define FLYWHEEL_2 4
#define LEFT_TOP_LIFT_MOTOR 1
#define LEFT_BOTTOM_LIFT_MOTOR 2

// Radio and Controllers Port Definitions
#define VEX_RADIO 21

// V5 Sensors
#define VISION_PORT 15
#define INERTIAL_PORT 7

// Tri Port Assignments, Ports A-H are mapped to 1-8
#define PNEUMATIC_LIFT_CLAW 1
#define PNEUMATIC_BACK_CLAW 2

#define LATERAL_BASE_ENCODER_TOP 3
#define LATERAL_BASE_ENCODER_BOTTOM 4

// Define Default Autonomous Behavior
#define DEFAULT_RECAUTON false
#define DEFAULT_SELECTION 0

#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code

#endif
