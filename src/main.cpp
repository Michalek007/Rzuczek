#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "esp32-hal-ledc.h"
#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include <Adafruit_Sensor.h>

#include "motor.h"
#include "hcsr04.h"
#include "servo.h"

#define waterPin GPIO_NUM_34
#define pumpPin GPIO_NUM_5
#define limitPin GPIO_NUM_35

/* Assign a unique ID to this sensor at the same time */
BluetoothSerial SerialBT;
Adafruit_BMP280 bmp; // I2C

int last_degree{0};
bool auto_enable{false};
int pump_pin_value{1};

void setup() {
  ledcSetup(enAB, 500, 8); // channel 1, 500 Hz, 8-bit width
  ledcAttachPin(enABpin, enAB); //GPIO 2 assigned to channel 1

  ledcSetup(servoChannel, 500, 8); // channel 3, 500 Hz, 8-bit width
  ledcAttachPin(servoPin, servoChannel); //GPIO 5 assigned to channel 3

  // pins for motors
  gpio_set_direction(in1, GPIO_MODE_OUTPUT);
  gpio_set_direction(in2, GPIO_MODE_OUTPUT);
  gpio_set_direction(in3, GPIO_MODE_OUTPUT);
  gpio_set_direction(in4, GPIO_MODE_OUTPUT);

 // pins for sensor
  gpio_set_direction(trigger_pin, GPIO_MODE_OUTPUT);
  gpio_set_direction(echo_pin, GPIO_MODE_INPUT);

  gpio_set_direction(waterPin, GPIO_MODE_INPUT);
  gpio_set_direction(pumpPin, GPIO_MODE_OUTPUT);
  gpio_set_direction(limitPin, GPIO_MODE_INPUT);

  gpio_set_level(pumpPin, 1);

  Serial.begin(921600);
  SerialBT.begin("rzuczek"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  // BMP280 setup
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
  }


  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                  

}

void loop() {

  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  delay(50);

  if (SerialBT.available()) {
    String dir = SerialBT.readStringUntil('s');
    Serial.println(dir);
    if (dir == "u"){
      // goes forward untill stop
      move_forward(128);
    }
    if (dir == "d"){
      // goes backward untill stop
      move_backward(128);
    }
    if (dir == "r"){
      // turns right 30 degrees  
      turn_right(333);
    }
    if (dir == "l"){
      // turns left 30 degrees
      turn_left(333);
    }
    if (dir == "x"){
      // stops motor
      motor_reset();
    }
    if (dir == "vu"){
      // servo position down
      set_servo_position(240, last_degree);
      last_degree = 240;
      if (!gpio_get_level(waterPin)){
          gpio_set_level(pumpPin, 0);
          delay(1000);
          gpio_set_level(pumpPin, 1);
          pump_pin_value = 1;
      }
    }
    if (dir == "vd"){
      // servo position up
      set_servo_position(70, 0);
      last_degree = 70;
    }
    if (dir == "p"){
      // pump enable/disable
      if (pump_pin_value == 1){
        gpio_set_level(pumpPin, 0);
        pump_pin_value = 0;
      }
      else{
        gpio_set_level(pumpPin, 1);
        pump_pin_value = 1;
      }
    }
    if (dir == "a"){
      // autonomous driving enable/disable
      auto_enable = !auto_enable;
    }
  }
  if (auto_enable == true){
    if (check_distance() <= 20){
      motor_reset();
      turn_left(333);
      move_forward(128);
   }
   else{
      move_forward(128);
   }
  }
}
