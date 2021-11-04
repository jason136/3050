#ifndef _CONVEYOR_H_
#define _CONVEYOR_H_

// Set voltage of conveyor motor without programmed stop, takes int from -127 to 127
void conveyorMove(int voltage);

// Sets voltage of conveyor motor to 0
void conveyorStop();

#endif
