#ifndef _INIT_H_
#define _INIT_H_

#include "api.h"

#define NUM_SCRIPTS 5         // Number of autonomous scripts to select from
                              // array index is does 0 - 4

//Call button objects
//Used to select autonomous routine

void on_left_button();        // left side created button

void on_center_button();      // center created button

void on_right_button();       // right side created button

#endif
