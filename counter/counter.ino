#include <Bridge.h>

#include "thingspeakReceiver.h"
ThingspeakReceiver thingspeakReceiver;

#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define PIN_LED_KO    12
#define PIN_LED_OK    13

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  pinMode(PIN_LED_KO, OUTPUT);
  pinMode(PIN_LED_OK, OUTPUT);

  _setKO();

  Bridge.begin(); //Yun Bridge
  Serial.begin(9600);
  while (!Serial);

  matrix.begin(0x70);
  matrix.setBrightness(2);
  displayCounter(0);

  thingspeakReceiver.init();

  Serial.println("Counter Up !!!");

  _setOK();

}

void loop() {
  int counter = thingspeakReceiver.receiveCounter();

  displayCounter(counter);

  delay(100);
}

void displayCounter(int counter) {
  matrix.print(counter);
  matrix.writeDisplay();

  Serial.println(counter);
}


void _setOK() {
  digitalWrite(PIN_LED_KO, LOW);
  digitalWrite(PIN_LED_OK, HIGH);
}

void _setKO() {
  digitalWrite(PIN_LED_OK, LOW);
  digitalWrite(PIN_LED_KO, HIGH);
}
