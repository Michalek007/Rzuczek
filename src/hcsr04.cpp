#include "hcsr04.h"

float check_distance()
{
    gpio_set_level(trigger_pin, 0);
    delay(1);

    gpio_set_level(trigger_pin, 1); //set the trigger high for 1ms
    delayMicroseconds(12); //minimum 10us pulse

    //reset back to 0
    gpio_set_level(trigger_pin, 0);

    int time_delay = pulseIn(echo_pin, 1);
    
    float distance = time_delay * sound_speed / 2; //distance in meters

    return distance / 100; // return in cm
}
