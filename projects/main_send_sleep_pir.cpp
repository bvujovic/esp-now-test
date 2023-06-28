#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

extern "C"
{
#include "user_interface.h" // za rad sa RTC memorijom
}
#define RTC_MEM_START (100)
int retry_itvs[] = {0, 2, 5};
enum Status
{
  FAILED = -1,
  UNKOWN,
  SUCCESS
};
Status sendStatus = UNKOWN;

uint8_t mac[] = {0xCC, 0x50, 0xE3, 0x0F, 0x62, 0x84};
char msg[50] = "id=0.0;pir=1;t=88.123";

void rtcWriteSleep(unsigned int itvRetry)
{
  system_rtc_mem_write(RTC_MEM_START, &itvRetry, 1);
  ESP.deepSleep(itvRetry == 0 ? 0 : retry_itvs[itvRetry] * 1000000UL);
}

void goToSleep(Status status)
{
  unsigned int itvRetry;
  system_rtc_mem_read(RTC_MEM_START, &itvRetry, 1);
  Serial.println(itvRetry);
  if (sendStatus == FAILED)
  {
    itvRetry++;
    if (itvRetry < sizeof(retry_itvs) / sizeof(int))
      rtcWriteSleep(itvRetry);
    else
      rtcWriteSleep(0);
  }
  else
    rtcWriteSleep(0);
}

void onDataSent(uint8_t *mac_addr, uint8_t status)
{
  Serial.print("Last Packet Send Status: ");
  sendStatus = (status == 0) ? SUCCESS : FAILED;
  Serial.println(sendStatus);
  goToSleep(sendStatus);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0)
  {
    Serial.println("ESP NOW INIT FAIL");
    goToSleep(FAILED);
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(onDataSent);
  esp_now_add_peer(mac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_send(mac, (uint8_t *)&msg, strlen(msg));
}

void loop()
{
}
