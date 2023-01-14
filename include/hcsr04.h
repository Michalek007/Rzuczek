#include <Arduino.h>

#define sound_speed 343

//pin defines
#define echo_pin GPIO_NUM_21 //change this later
#define trigger_pin GPIO_NUM_19 //change this later

//returns the distance in cm
int check_distance();
