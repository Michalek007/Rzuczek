// /*
//   Rui Santos
//   Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files.

//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
// */

// #include <WiFi.h>
// #include <HTTPClient.h>

// const char* ssid = "first";
// const char* password = "1234";

// //Your Domain name with URL path or IP address with path
// String serverName = "http://127.0.0.1:5000/login";

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
