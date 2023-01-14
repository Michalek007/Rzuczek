#include "servo.h"


void set_servo_position(int degree){
    for (int i = 0; i < degree;i+=5){
        ledcWrite(servoChannel, i);
    }
}

void reset_servo_position(){
    ledcWrite(servoChannel, 0);
}
