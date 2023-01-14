#include <Arduino.h>
#include "esp32-hal-ledc.h"

void setup() {
    ledcSetup(1, 50, 16); // channel 1, 50 Hz, 16-bit width
    ledcAttachPin(2, 1); //GPIO 22 assigned to channel 1
}

void loop() {
    for (int i = 0; i < 8000; i = i + 100){
        ledcWrite(1, i); //sweep servo 
        delay(50);
    }
}
