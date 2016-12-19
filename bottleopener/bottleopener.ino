#include <Bridge.h>

#include "thingspeakSender.h"
ThingspeakSender thingspeakSender;

#define PIN_BUTTON    7
#define PIN_LED_KO    12
#define PIN_LED_OK    13

//Global counter for this bottle opener
int counter = 0;

void setup() {
  pinMode(PIN_LED_KO, OUTPUT);
  pinMode(PIN_LED_OK, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

  _setKO();

  //setup the bridge and serial
  Bridge.begin(); //Yun Bridge
  Serial.begin(9600);
  while (!Serial);

  //setup the IoT platforms
  thingspeakSender.init();

  //Everything seems to be ok, let's start !
  Serial.println("Bottle Opener Up !!!");
  _setOK();
}

/**
   Arduino loop...
*/
void loop() {
  boolean pressed = debounce();
  if (pressed == true) {
    counter++;
    Serial.print("Button pressed ");
    Serial.print(counter);
    Serial.println(" times");
    sendCounter();
  }

}

/**
   Send the counter to the IoT platforms
*/
void sendCounter() {
  thingspeakSender.sendCounter(counter);
}

/**
   check if the button was pressed.
*/
boolean debounce() {
  static int buttonState;
  static int lastButtonState = LOW;
  static long lastDebounceTime = 0;
  static long debounceDelay = 50;

  boolean retVal = false;
  int reading = digitalRead(PIN_BUTTON);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        retVal = true;
      }
    }
  }
  lastButtonState = reading;
  return retVal;
}

/**
   Lightup the blue led
*/
void _setOK() {
  digitalWrite(PIN_LED_KO, LOW);
  digitalWrite(PIN_LED_OK, HIGH);
}

/**
   Light up the red led
*/
void _setKO() {
  digitalWrite(PIN_LED_OK, LOW);
  digitalWrite(PIN_LED_KO, HIGH);
}
