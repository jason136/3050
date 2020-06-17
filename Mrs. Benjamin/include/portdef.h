#ifndef PORT_DEF_H_
#define PORT_DEF_H_

// Motor Port Definitions
// Drive Base Motors
#define RIGHT_MOTOR_PORT 10
#define LEFT_MOTOR_PORT 9

// Tray Motor
#define TRAY_MOTOR1_PORT 7
#define TRAY_MOTOR2_PORT 20

// Lift Motor
#define RIGHT_LIFT_MOTOR_PORT 5
#define LEFT_LIFT_MOTOR_PORT 6

// Roller Motors
#define RIGHT_ROLLER_MOTOR_PORT 4
#define LEFT_ROLLER_MOTOR_PORT 19

// Radio and Controllers Port Definitions
#define VEX_RADIO 21
 
// GLOBAL DEBUGGING Variables
#define DEBUG_ON true

#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code
#define VEXNET_TIME 15            // 15 seconds or other time to run
                                  // not yet implemented

#endif
