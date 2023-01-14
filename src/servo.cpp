#include "servo.h"

void set_servo_position(int degree){
    ledcWrite(2, degree);
}

void reset_servo_position(){
    ledcWrite(servoChannel, 0);
}
