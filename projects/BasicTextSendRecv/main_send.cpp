//* https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/

#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

const byte pinLed = LED_BUILTIN;

// CC:50:E3:0F:62:84
// uint8_t mac[] = {0xCC, 0x50, 0xE3, 0x0F, 0x62, 0x84};
uint8_t mac[] = {0x84, 0xF3, 0xEB, 0x77, 0x04, 0xBA};

bool sendSuccess = true;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
{
  Serial.print("Last Packet Send Status: ");
  Serial.println((sendSuccess = sendStatus == 0) ? "Success" : "FAIL");
}

void setup()
{
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, true);
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  // Serial.println(WiFi.macAddress());
  if (esp_now_init() != 0)
  {
    Serial.println("ESP NOW INIT FAIL");
    while (true)
      delay(100);
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(mac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

char msg[] = "Pozdrav ESP-Now";

void loop()
{
  if (!sendSuccess)
    digitalWrite(pinLed, false);
  delay(1000);
  digitalWrite(pinLed, true);
  esp_now_send(mac, (uint8_t *)&msg, strlen(msg));
  delay(4000);
}
