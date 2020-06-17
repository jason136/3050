#include "main.h"
#include "portdef.h"
#include "lift.h"
#include "chassis.h"
#include "shooter.h"
#include "intake.h"
#include "claw.h"


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);						// MASTER remote for driving
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);					// PARTNER remote for lift

  int left = 0;					// left motor speed control
	int right = 0;				// right motor speed control

	double scaling = 1.0;

  extern int selection;

	bool autoRun = true;

  int clawState = 0;		// track if we are flipped or need to reflip.

	/*
  // Manual VEXNET code removed for competition
	while(VEXNET_MANUAL && autoRun) {
		 // CODE To test Autonomous without VEXnet switch
		 // This should never be part of production code
		 if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			   std::cout << "VEXnet Manual section \n";
			 	 std::cout << "Calling autonomous function \n";
				 selection = 1;								// need to transmit LCD selection as we do not
				 															// get to LCD selection screen in bootup sequence
				 autonomous();
		 } else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
				 autoRun = false;
				 std::cout << "VEXnet Manual section \n";
         std::cout << "Dropping out of autonomous \n";
		 }
		 pros::delay(40);				// Slow the thread down
	}
  */

  if (partner.is_connected()) {
		if(DEBUG_ON) {
			std::cout << "Partner Remote is connected \n";
			liftLockMode();
		}
	}

	while (true) {
    // get speed control -- using button X to rotate through .75, .5 and .25 speed scaling
		// When button B is presses it reset to 1:1 scaling
		//if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			// reduce scaling .25, however if scaling is alread .25 then we reset to 1:1
		//	if(scaling != .25) {
		//		scaling = scaling - 0.25;				// scale down .25
		//	} else {
		//		scaling = 1;										// scaling was at lowest so reset to 1:1
		//	}
    //}
		// RESET scaling button
		//if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
    //	 scaling = 1;					// reset the scaling to 1:1
		//}

    // check if we are wanting to drive in ARCADE or TANK drive mode.  If the
		// global ARCADE_DRIVE == true we will execute aracade drive otherwise we will
		// be using TANK_MODE

    if(ARCADE_DRIVE) {
	     left = master.get_analog(ANALOG_LEFT_Y);
		   right = master.get_analog(ANALOG_LEFT_X);

			 // implemenet dead stick control
			 if(abs(left) < DEAD_STICK) { left = 0; }
			 if(abs(right) < DEAD_STICK) { right = 0; }

			 chassisSetOpcontrol(left + right, left - right);
    } else {
       // we are wanting to do TANK Control
			 left = master.get_analog(ANALOG_LEFT_Y);
			 right = master.get_analog(ANALOG_RIGHT_Y);

			 // implemenet dead stick control
			 if(abs(left) < DEAD_STICK) { left = 0; }
			 if(abs(right) < DEAD_STICK) { right = 0; }

      /*
       if(DEBUG_ON) {
				 std::cout << "Scaling: " << scaling ;
				 std::cout << " Left: " << left ;
			 }
			 */

       // lets do JOY stick scaling as well
			 left = (left * scaling);
			 right = (right * scaling);
       /*
			 if(DEBUG_ON) {
				std::cout << " Left Scaled: " << left << "\n" ;
			}
			*/
	  	 chassisSetOpcontrol(left, right);
    }

    // Ball Shooter Control
		//if(master.get_digital_new_press(DIGITAL_LEFT)){
		// Moved to button B - 3/5/2019
		if(master.get_digital_new_press(DIGITAL_Y)){
			shootBall(100);
		}

		// Run the intake
		if(master.get_digital(DIGITAL_L1)) {
			intakeForward(200);
		} else if(master.get_digital(DIGITAL_L2)) {
			intakeBackward(200);
		} else {
			intakeStop(0);
		}

		//flip claw
		//if(master.get_digital_new_press(DIGITAL_RIGHT)){
		if(master.get_digital_new_press(DIGITAL_A)){

			if(clawState == 0){
				flipClaw(100);										// Flip the claw 180 degrees at speed in RPM
				clawState = 1;
			}
			else{
				flipClawBack(100);								// Flip the claw -180 degrees at speed in RPM
																					// back to opposite position
				clawState = 0;
			}
		}

    // RESET CLAW PID to 0 Position
		// Moved to partner remote
		//if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
		//	 setClawPosition();
		//}

		// Control lift movement
		if(master.get_digital(DIGITAL_R1)) {
			liftRaise(100, 1);					// raise to middle pole
		} else if(master.get_digital(DIGITAL_R2)) {
			liftRaise(100, 2);					// raise to high pole
		} else {
			// stay put lock it
		}

		// lift reteact to zero
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			 liftRaise(150, 0);
		}
		pros::delay(20);

		//if (partner.is_connected()) {
      // Use a two controller control scheme -- PARTNER is connected

			// get speed control -- using button X to rotate through .75, .5 and .25 speed scaling
			// When button B is presses it reset to 1:1 scaling
			if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
				// reduce scaling .25, however if scaling is alread .25 then we reset to 1:1
				if(scaling != .25) {
					scaling = scaling - 0.25;				// scale down .25
				} else {
					scaling = 1;										// scaling was at lowest so reset to 1:1
				}
	    }
			// RESET scaling button
			if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
	    	 scaling = 1;					// reset the scaling to 1:1
			}

			// Control lift movement
			if(partner.get_digital(DIGITAL_L1)) {
				liftRaiseManual(100);						// raise
			} else if(partner.get_digital(DIGITAL_L2)) {
				liftRaiseManual(-100);					// lower
			} else {
				// stay put lock it
				liftLock();
			}

			// Move lift in defined increments up/down
			if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
   			liftRaiseStep(50, 1);				// MOVE lift up at 50RPM
			}
			if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
				liftRaiseStep(50, 0);				// MOVE lift up at 50RPM
			}

			// Drop Cap auto function
			if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
				liftDropCap(75);				// MOVE lift up at 50RPM
			}

			// Lift slightly in preparatio nfor cap flip
			if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
				 liftRaiseForEncoder(100, LIFT_FLIP_RAISE);				// MOVE lift up to be ready
				 																									// to flip cap
			}

			// RESET CLAW PID to 0 Position
			//if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
				 setClawPosition();
			}
    //}
	}
}
