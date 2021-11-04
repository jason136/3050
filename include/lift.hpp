#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

// Set voltage of front lift without programmed stop, takes int from -127 to 127
void frontLiftMove(int voltage);

// lock the front lift where it is right now....
void frontLiftLock();

// Set voltage of back lift without programmed stop, takes int from -127 to 127
void backLiftMove(int voltage);

// lock the back lift where it is right now....
void backLiftLock();

#endif
