#include <Arduino.h>

char msg[] = "id=0;t=88.123;";

// Za s:"id=0;t=2.3;" i name:"t", vraca "2.3"
char *getStrValue(char *s, const char *name)
{
  if (*s == '\0')
    return NULL;
  size_t n = strlen(name);      // duzina imena parametra cija se vrednost trazi
  if (strncmp(s, name, n) == 0) // ako je pronadjen parametar sa trazenim imenom...
  {
    int i = 0;
    while (s[n + i + 1] != ';') // racunanje duzine vrednosti (string)
      i++;
    char *strVal = (char *)malloc(i + 1);
    strncpy(strVal, s + n + 1, i);
    strVal[i] = '\0';
    return strVal;
  }
  // ovo se izvrsava ako parametar sa datim imenom nije pronadjen
  s += n + 1;       // preskace se ime i '='
  while (*s != ';') // i vrednost tekuceg parametra sve do ';'
    s++;
  return getStrValue(s + 1, name); // rekurzivno se poziva fja od karaktera iz ';'
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.println(msg);
  char *strVal = getStrValue(msg, "t");
  Serial.println(strVal);
  Serial.println(getStrValue(msg, "id"));
  Serial.println(getStrValue(msg, "abc"));

  Serial.println(ESP.getFreeHeap());
  for (size_t i = 0; i < 100; i++)
  {
    char *str;
    // getStrValue(msg, "id");
    str = getStrValue(msg, "t");
    // double temp = atof(str);
    free(str);
    // Serial.println(temp);
  }
  Serial.println(ESP.getFreeHeap());

  ESP.deepSleep(0);
}

void loop() {}
