#include <Arduino.h>
#include "motor.h"
#include "esp32-hal-ledc.h"

void setup() {
  ledcSetup(enA, 50, 8); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(enApin, enA); //GPIO 2 assigned to channel 1
  
  ledcSetup(enB, 50, 8); // channel 2, 50 Hz, 16-bit width
  ledcAttachPin(enBpin, enB); //GPIO 4 assigned to channel 2

  gpio_set_direction(in1, GPIO_MODE_OUTPUT);
  gpio_set_direction(in2, GPIO_MODE_OUTPUT);
  gpio_set_direction(in3, GPIO_MODE_OUTPUT);
  gpio_set_direction(in4, GPIO_MODE_OUTPUT);

  Serial.begin(921600);
}

void loop() {
  move_forward(128);
}
