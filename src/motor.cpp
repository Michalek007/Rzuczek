#include "motor.h"
#include <Arduino.h>

void motor_set(Motor motor, Direction dir, int speed)
{
    if(motor == Motor::A)
    {
        ledcWrite(enA, speed);
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
    }
    if(motor == Motor::B)
    {
        ledcWrite(enB, speed);
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
    }

}

void move_forward(int speed)
{
    motor_set(Motor::A, Direction::cw, speed);
    motor_set(Motor::B, Direction::ccw, speed);
}


void move_backward(int speed)
{
    motor_set(Motor::A, Direction::ccw, speed);
    motor_set(Motor::B, Direction::cw, speed);
}


void turn_left(int angle)
{
    motor_set(Motor::A, Direction::cw, 0);
    motor_set(Motor::B, Direction::cw, 0);

    delay(100);

    motor_set(Motor::B, Direction::ccw, 10);

    delay(angle);

    motor_set(Motor::B, Direction::cw, 0);
}


void turn_right(int angle)
{
    motor_set(Motor::A, Direction::cw, 0);
    motor_set(Motor::B, Direction::cw, 0);

    delay(100);

    motor_set(Motor::A, Direction::cw, 10);

    delay(angle);

    motor_set(Motor::A, Direction::cw, 0);
}
