#include <Arduino.h>

#define enA 2
#define enB 3
#define in1 4
#define in2 5 
#define in3 6
#define in4 7

enum class Motor
{
    A = 0,
    B = 1
};

enum class Direction
{
    forward = 0,
    backward = 1,
    cw = 2,
    ccw = 3
};

//set single motor direction and speed
void motor_set(Motor motor, Direction dir, int speed);

void move_forward(int speed);

void move_backward(int speed);

void turn_left(int angle);

void turn_right(int angle);
