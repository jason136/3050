#ifndef PORT_DEF_H_
#define PORT_DEF_H_

// right lift 8,9;; 7 is left lift; 6 is intake; 5 is shooter; four is mnipulstor; 3 is left drive; 2 is right

// LIFT control Motors
#define LIFT_RIGHT_MOTOR_PORT  7
#define LIFT_RIGHT_MOTOR_PORT_TWO  9
#define LIFT_LEFT_MOTOR_PORT  8

// INTAKE roillers Motors
#define INTAKE_MOTOR_PORT 6

// Ball launcher Motors
#define SHOOTER_MOTOR_PORT 5

// Cap flipper Motors
#define CLAW_MOTOR_PORT 4

// Drive Base Motors
#define DRIVE_LEFT_MOTOR_PORT 3
#define DRIVE_LEFT_MOTOR_PORT2 19

#define DRIVE_RIGHT_MOTOR_PORT 2
#define DRIVE_RIGHT_MOTOR_PORT2 20
// ----------- Radio and Controllers ---------------
#define VEX_RADIO 21

// ------------ Vision Sensors ---------------------
#define VISION_ONE 14

// ----------- LEGACY port assignements ------------

// ----------- GLOBAL DEBUGGING Variables ----------
#define DEBUG_ON true

#define VEXNET_MANUAL true        // turns opcontrol into allowing for
                                  // testing autonomous code
#define VEXNET_TIME 15            // 15 seconds or other time to run
                                  // not yet implemented

#endif
