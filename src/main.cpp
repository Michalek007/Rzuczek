#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "esp32-hal-ledc.h"
#include "BluetoothSerial.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include "motor.h"
#include "hcsr04.h"
#include "servo.h"

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DESKTOP-O2OLJ1H 8056";
const char* password = "L5w7393^";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.137.1:5000";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


#define waterPin GPIO_NUM_34
#define pumpPin GPIO_NUM_5
#define limitPin GPIO_NUM_35

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
BluetoothSerial SerialBT;
Adafruit_BMP280 bmp; // I2C
Adafruit_SSD1306 display(-1);
sensors_event_t event; 

void setup() {
  ledcSetup(enAB, 500, 8); // channel 1, 500 Hz, 8-bit width
  ledcAttachPin(enABpin, enAB); //GPIO 2 assigned to channel 1

  ledcSetup(servoChannel, 500, 8); // channel 3, 500 Hz, 8-bit width
  ledcAttachPin(servoPin, servoChannel); //GPIO 5 assigned to channel 3

  gpio_set_direction(in1, GPIO_MODE_OUTPUT);
  gpio_set_direction(in2, GPIO_MODE_OUTPUT);
  gpio_set_direction(in3, GPIO_MODE_OUTPUT);
  gpio_set_direction(in4, GPIO_MODE_OUTPUT);

  gpio_set_direction(trigger_pin, GPIO_MODE_OUTPUT);
  gpio_set_direction(echo_pin, GPIO_MODE_INPUT);

  gpio_set_direction(waterPin, GPIO_MODE_INPUT);
  gpio_set_direction(pumpPin, GPIO_MODE_OUTPUT);
  gpio_set_direction(limitPin, GPIO_MODE_INPUT);

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
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {

  /* Get a new sensor event */
  // accel.getEvent(&event);

  // /* Display the results (acceleration is measured in m/s^2) */
  // Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  // Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  // Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  // delay(500);
  // ustawiamy rozmiar czcionki, kolor, położenie kursora orazwyświetlany tekst
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(5, 10);
  // display.println("DUPA");
  // display.display();
  // display.clearDisplay();
  // delay(2000);

  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0,28);
  // display.println("Hello world!");
  // display.display();

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

  // // if (Serial.available()) {
  // //   SerialBT.write(Serial.read());
  // // }

  if (SerialBT.available()) {
    String dir = SerialBT.readStringUntil('s');
    Serial.println(dir);
    if (dir == "u"){
      move_forward(128);
    }
    if (dir == "d"){
      move_backward(128);
    }
    if (dir == "r"){
      turn_right(1000);
    }
    if (dir == "l"){
      turn_left(1000);
    }
    if (dir == "x"){
      motor_reset();
    }
    if (dir == "vu"){
      set_servo_position(128);
    }
    if (dir == "vr"){
      set_servo_position(255);
    }
  }
  delay(10);
  Serial.println(gpio_get_level(limitPin));
  delay(10);  
  float distance{0};
  distance = check_distance();
  Serial.println(distance);
  delay(10);
  Serial.println(gpio_get_level(waterPin));
  delay(10);
}



// void setup() {
//   Serial.begin(921600);; 

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());
 
//   Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
// }

// void loop() {
//   //Send an HTTP POST request every 10 minutes
//   if ((millis() - lastTime) > timerDelay) {
//     //Check WiFi connection status
//     if(WiFi.status()== WL_CONNECTED){
//       HTTPClient http;

//       float temp = 2.3;
//       float press = 2.3;
//       float absl = 2.3;

//       String values = "?temp=" + String(temp) + "&press=" + String(press) + "&absl=" + String(absl);
//       String serverPath = serverName + "/parameters/" + values;
      
//       // Your Domain name with URL path or IP address with path
//       http.begin(serverPath.c_str());
      
//       // If you need Node-RED/server authentication, insert user and password below
//       //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
//       // Send HTTP GET request
//       int httpResponseCode = http.GET();
      
//       if (httpResponseCode>0) {
//         Serial.print("HTTP Response code: ");
//         Serial.println(httpResponseCode);
//         String payload = http.getString();
//         Serial.println(payload);
//       }
//       else {
//         Serial.print("Error code: ");
//         Serial.println(httpResponseCode);
//       }
//       // Free resources
//       http.end();
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     lastTime = millis();
//   }
// }
