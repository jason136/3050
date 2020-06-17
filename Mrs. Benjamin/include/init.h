#ifndef _INIT_H_
#define _INIT_H_

#include "api.h"

#define NUM_SCRIPTS 5         // Number of autonomous scripts to select from
                              // array index is does 0 - 4

// Various functiosn to interact with the V5 lcd display, predominantly
// to facilitate Qutonomous Selections.
// Button setup matches the old style LCD display with the cortex

void on_left_button();        // left side created button

void on_center_button();      // center created button

void on_right_button();       // right side created button

#endif
