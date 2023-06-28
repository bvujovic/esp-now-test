// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/
// To communicate via ESP-NOW, you need to know the MAC Address of the ESP8266 receiver.
// My NodeMCU MAC address: 84:F3:EB:77:04:BA

#include <ESP8266WiFi.h>

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop(){
}
