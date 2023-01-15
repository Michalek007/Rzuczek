#include "servo.h"


void set_servo_position_up(int degree, int last_degree){
    for (int i = last_degree; i < degree;i+=5){
        ledcWrite(servoChannel, i);
    }
}
