#ifndef PORT_DEF_H_
#define PORT_DEF_H_

// Motor Port Assignments
// Drive Base Motors
#define FRONT_RIGHT_DRIVE_MOTOR 2
#define FRONT_LEFT_DRIVE_MOTOR 5
#define BACK_RIGHT_DRIVE_MOTOR 6
#define BACK_LEFT_DRIVE_MOTOR 10

// Lift Motor
#define FLYWHEEL_1 14
#define FLYWHEEL_2 18

// Indexer Motor
#define INDEXER_MOTOR 3

// Intake Motor
#define INTAKE_1 8
#define INTAKE_2 9

// Radio and Controllers Port Definitions
#define VEX_RADIO 11

// V5 Sensors
#define VISION_PORT 22
#define GPS_PORT 20
#define INERTIAL_PORT 12

// Tri Port Assignments, Ports A-H are mapped to 1-8
#define PNEUMATIC_INDEXER 1
#define PNEUMATIC_END_GAME 2
#define PNEUMATIC_BAT_WINGS 5

#define LATERAL_BASE_ENCODER_TOP 3
#define LATERAL_BASE_ENCODER_BOTTOM 4

// Define Default Autonomous Behavior
#define DEFAULT_RECAUTON false
#define DEFAULT_SELECTION 0

#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code

#endif
