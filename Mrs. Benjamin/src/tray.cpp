#include "main.h"
#include "tray.h"
#include "portdef.h"

pros::Motor trayMotor1(TRAY_MOTOR1_PORT);
pros::Motor trayMotor2(TRAY_MOTOR2_PORT);

void trayForward(int speed) {
  trayMotor1.move_velocity(speed);
  trayMotor2.move_velocity(speed);
}

void trayBackward(int speed) {
  trayMotor1.move_velocity(-speed);
  trayMotor2.move_velocity(-speed);
}

void trayStop(int speed) {
  trayMotor1.move_velocity(0);
  trayMotor2.move_velocity(0);
}

void traySpinForEncoder(int speed, int encDegrees) {
  trayMotor1.move_absolute(encDegrees, speed);

  if(DEBUG_ON){
    std::cout << "In Tray Raise Manual function -- Speed: " << speed ;
    std::cout << " Current Encoder: " << trayMotor1.get_position() << "\n";
  }
  trayMotor1.move_velocity(speed);
  trayMotor2.move_velocity(speed);
  pros::delay(2);
}

void trayLock() {
  if(trayMotor1.get_brake_mode() != 2 ) {
    trayMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  trayMotor1.move_velocity(0);
  trayMotor2.move_velocity(0);
  pros::delay(2);
}
