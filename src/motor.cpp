#include "motor.h"
#include <Arduino.h>

void motor_set(Motor motor, Direction dir, int speed)
{   
    if(motor == Motor::A)
    {
        if(dir == Direction::cw)
        {
            gpio_set_level(in1, 1);
            gpio_set_level(in2, 0);
        }
        else if(dir == Direction::ccw)
        {
            gpio_set_level(in1, 0);
            gpio_set_level(in2, 1);
        }
        ledcWrite(enA, speed);
        
    }
    if(motor == Motor::B)
    {
        if(dir == Direction::cw)
        {
            gpio_set_level(in3, 1);
            gpio_set_level(in4, 0);
        }
        else if(dir == Direction::ccw)
        {
            gpio_set_level(in3, 0);
            gpio_set_level(in4, 1);
        }
        ledcWrite(enB, speed);
    }

}

void move_forward(int speed)
{
    motor_reset();
    motor_set(Motor::A, Direction::cw, speed);
    motor_set(Motor::B, Direction::ccw, speed);
}


void move_backward(int speed)
{
    motor_reset();
    motor_set(Motor::A, Direction::ccw, speed);
    motor_set(Motor::B, Direction::cw, speed);
}


void turn_left(int angle)
{
    motor_reset();
    motor_set(Motor::A, Direction::ccw, 128);
    motor_set(Motor::B, Direction::ccw, 128);

    delay(angle);
}


void turn_right(int angle)
{
    motor_reset();
    motor_set(Motor::B, Direction::cw, 128);
    motor_set(Motor::A, Direction::cw, 128);

    delay(angle);
}

void motor_reset(){
    ledcWrite(enA, 0);
    ledcWrite(enB, 0);
    gpio_set_level(in1, 0);
    gpio_set_level(in2, 0);
    gpio_set_level(in3, 0);
    gpio_set_level(in4, 0);
}
