#include "main.h"    // includes API.h and other headers
#include "claw.h"    // ensures that the corresponding header file (intake.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included


pros::Motor clawMotor(CLAW_MOTOR_PORT);

void flipClaw(int speed){
  clawMotor.move_absolute(FLIP_TARGET, speed);    // flip the claw 180 degrees
}

void flipClawBack(int speed){
  clawMotor.move_absolute(0, speed);            // flip 180 degrees back
}

void setClawPosition(){
  clawMotor.tare_position();                    // reset the zero point
}
