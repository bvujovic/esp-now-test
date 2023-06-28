#include <Arduino.h>

const byte pinLed = LED_BUILTIN;

void setup()
{
    pinMode(pinLed, OUTPUT);
}

void loop()
{
    digitalWrite(pinLed, true);
    delay(1000);
    digitalWrite(pinLed, false);
    delay(1000);
}
