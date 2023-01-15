#include <Arduino.h>

#define enAB 1 //channel 1
#define enABpin 2
#define in1 GPIO_NUM_27
#define in2 GPIO_NUM_26
#define in3 GPIO_NUM_25
#define in4 GPIO_NUM_23

enum class Motor
{
    A = 0,
    B = 1
};

enum class Direction
{
    cw = 0,
    ccw = 1
};

int angle_to_time(int angle);

//set single motor direction and speed
void motor_set(Motor motor, Direction dir, int speed);

void move_forward(int speed);

void move_backward(int speed);

void turn_left(int angle);

void turn_right(int angle);

void motor_reset();
