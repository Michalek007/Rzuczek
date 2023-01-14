#include "servo.h"


void set_servo_position(int degree){
    ledcWrite(servoChannel, (degree*256)/180);
}

void reset_servo_position(){
    ledcWrite(servoChannel, 0);
}
