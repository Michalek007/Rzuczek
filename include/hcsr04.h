#include <Arduino.h>

#define sound_speed 3.43

//pin defines
#define echo_pin GPIO_NUM_19
#define trigger_pin GPIO_NUM_18

//returns the distance in cm
float check_distance();
