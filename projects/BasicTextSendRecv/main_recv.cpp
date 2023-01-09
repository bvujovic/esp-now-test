//* https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/

#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

// char msg[100];

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
  Serial.println("Data received!");
  Serial.println(len);
  Serial.println((char *)incomingData);
  // memcpy(msg, incomingData, len);
  // Serial.println(msg);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\nReceiving data...");
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0)
  {
    Serial.println("ESP NOW INIT FAIL");
    while (true)
      delay(100);
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
}
