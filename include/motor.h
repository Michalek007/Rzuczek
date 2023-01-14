#include <Arduino.h>

#define enA 1 //channel 1
#define enB 2 //channel 2
#define enApin 2
#define enBpin 4
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
    cw = 2,
    ccw = 3
};

int angle_to_time(int angle);

//set single motor direction and speed
void motor_set(Motor motor, Direction dir, int speed);

void move_forward(int speed);

void move_backward(int speed);

void turn_left(int angle);

void turn_right(int angle);

void motor_reset();
