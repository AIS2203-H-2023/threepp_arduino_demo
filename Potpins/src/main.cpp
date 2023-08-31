#include "ArduinoJson.hpp"
#include <Arduino.h>

#include "Potpin.hpp"

using namespace ArduinoJson;

int main() {

  init(); // arduino requirement

  Serial.begin(9600);

  Potpin p1(A0);
  Potpin p2(A1);
  StaticJsonDocument<16> doc;

  while (true) {
    int potVal1 = p1.read();
    int potVal2 = p2.read();

    doc["potVal1"] = potVal1;
    doc["potVal2"] = potVal2;

    serializeJson(doc, Serial);
    Serial.println();

    delay(100);
  }
}
