#ifndef PORT_DEF_H_
#define PORT_DEF_H_

// Motor Port Assignments
// Drive Base Motors
#define FRONT_RIGHT_DRIVE_MOTOR 17
#define FRONT_LEFT_DRIVE_MOTOR 18
#define BACK_RIGHT_DRIVE_MOTOR 19
#define BACK_LEFT_DRIVE_MOTOR 20

// Tray Motor
#define TRAY_MOTOR_PORT 5
#define CLAW_MOTOR 10
#define GRABBER_MOTOR 6

// Lift Motor
#define RIGHT_TOP_LIFT_MOTOR 3
#define RIGHT_BOTTOM_LIFT_MOTOR 4
#define LEFT_TOP_LIFT_MOTOR 1
#define LEFT_BOTTOM_LIFT_MOTOR 2

// Radio and Controllers Port Definitions
#define VEX_RADIO 21

// V5 Sensors
#define VISION_PORT 100
#define INERTIAL_PORT 11

// Tri Port Assignments, Ports A-H are mapped to 1-8
#define PNEUMATIC_PORT_MOBILE_GOAL 2
#define PNEUMATIC_PORT_AUTONOMOUS_1 1
#define PNEUMATIC_PORT_AUTONOMOUS_2 8
#define LATERAL_BASE_ENCODER_TOP 3
#define LATERAL_BASE_ENCODER_BOTTOM 4

// Define Default Autonomous Behavior
#define DEFAULT_RECAUTON false
#define DEFAULT_SELECTION 2

// Define Which Robot we are Compiling for
#define FLIP_FLOP false

#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code

#endif
