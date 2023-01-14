#include <Arduino.h>
#include "esp32-hal-ledc.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include "motor.h"
#include "hcsr04.h"

BluetoothSerial SerialBT;

void setup() {
  ledcSetup(enA, 500, 8); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(enApin, enA); //GPIO 2 assigned to channel 1
  
  ledcSetup(enB, 500, 8); // channel 2, 50 Hz, 16-bit width
  ledcAttachPin(enBpin, enB); //GPIO 4 assigned to channel 2

  gpio_set_direction(in1, GPIO_MODE_OUTPUT);
  gpio_set_direction(in2, GPIO_MODE_OUTPUT);
  gpio_set_direction(in3, GPIO_MODE_OUTPUT);
  gpio_set_direction(in4, GPIO_MODE_OUTPUT);

  gpio_set_direction(trigger_pin, GPIO_MODE_OUTPUT);
  gpio_set_direction(echo_pin, GPIO_MODE_INPUT);

  Serial.begin(921600);
  // Serial.begin(115200);
  SerialBT.begin("rzuczek"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
    // if (Serial.available()) {
    //   SerialBT.write(Serial.read());
    // }
    if (SerialBT.available()) {
      String dir = SerialBT.readStringUntil('s');
      Serial.println(dir);
      // Serial.println(SerialBT.readString());
      // switch (dir[0]){
      //   case 'u':
      //     move_forward(128);
      //   case 'd':
      //     move_backward(128);
      //   case 'l':
      //     turn_left(2000);
      //   case 'r':
      //     turn_right(2000);
      //   case 'x':
      //     motor_reset();
      // }
      if (dir == "u"){
        move_forward(128);
      }
      if (dir == "d"){
        move_backward(128);
      }
      if (dir == "r"){
        turn_right(2000);
      }
      if (dir == "l"){
        turn_left(2000);
      }
      if (dir == "x"){
        motor_reset();
      }
      // Serial.write(SerialBT.read());
    }
      delay(10);

  // float distance{0};
  // distance = check_distance();
  // Serial.println(distance);
  // delay(500)  ;
  
  // while (true){
  //   turn_right(2000);
  //   turn_left(2000);
  //   move_forward(128);
  //   delay(2000);
  //   move_backward(128);
  //   delay(2000);
  // }
}
