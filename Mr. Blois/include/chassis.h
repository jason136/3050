#ifndef _CHASSIS_H_
#define _CHASSIS_H_

//Chassis related globals

#define WHEEL_DIAMETER 4      // diameter of drive wheels
#define WHEEL_BASE 11.5       // wheel base in inches left to right wheel diagonal measured
                              // of chassis.

#define DRIVE_MODE 4          // 1 for x-drive TANK
                              // 2 for x-drive ARDCADE
                              // 3 for standard ARCADE
                              // 4 for standard TANK
                              // 5 for Ryan Mode (arcade but with the arrow keys for movement)

#define JOY_SCALE 1           // scale the joysticks to 50% valid values are 0 - 1
                              // note: 0 will disable joysticks 0 * x = 0 always....

#define DEAD_STICK 10         // Dead stick zone - joystick movement between
                              // -DEAD_STICK and DEAD_STICK will result in a joystick
                              // value of 0 - dealing with slow creepign of robot when joysticks
                              // do not land perfectly in the center position

#define MOTOR_MAX_SPEED 200   // Robot has 36 gearset (RED) for 18 gearset (GREEN) -- 200
                              // for 06 (BLUE) -- 600

// Going to wait and see if Connor's library can make our lives easier here. 



#endif
