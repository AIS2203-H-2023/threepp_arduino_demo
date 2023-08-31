#include "ArduinoJson.hpp"
#include <Arduino.h>

#include "Potpin.hpp"

using namespace ArduinoJson;

Potpin p1(A0);
Potpin p2(A1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int potVal1 = p1.read();
  int potVal2 = p2.read();

  StaticJsonDocument<16> doc;
  doc["potVal1"] = potVal1;
  doc["potVal2"] = potVal2;

  serializeJson(doc, Serial);
  Serial.println();

  delay(100);
}
