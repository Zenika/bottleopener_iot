#include <Bridge.h>

#include "thingspeakSender.h"
ThingspeakSender thingspeakSender;

#include "shiftrConnector.h"
ShiftrConnector shiftrConnector;

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
  shiftrConnector.init("bottleopener1", "c91dc205301b5f93");

  //Everything seems to be ok, let's start !
  Serial.println("Bottle Opener Up !!!");
  _setOK();
}

/**
   Arduino loop...
*/
void loop() {
  shiftrConnector.loop();

  
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
 * Only necessary for Shiftr.io API
 */
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}

/**
   Send the counter to the IoT platforms
*/
void sendCounter() {
  thingspeakSender.sendCounter(counter);
  shiftrConnector.sendCounter(counter);
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
