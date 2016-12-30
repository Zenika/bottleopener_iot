#include <Bridge.h>

#include "logger.h"

/////////////////////////////////////////////
// Include of Iot Platform's connectors
#include "thingspeakSender.h"
ThingspeakSender thingspeakSender;

#include "shiftrConnector.h"
ShiftrConnector shiftrConnector;
/////////////////////////////////////////////

#define PIN_BUTTON    7
#define PIN_LED      13

//Global counter for this bottle opener
int counter = 0;

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);

  Bridge.begin(); // Yun bridge
  logger->init();


  //setup the IoT platforms
  logger->log("Start setup connection with IoT platforms...\n");
  thingspeakSender.init();
  shiftrConnector.init();

  //Everything seems to be ok, let's start !
  logger->log("\nBottle Opener up, Let's start to play :) !!!\n");

  //highlight blue led just to prevent everything is OK. Useful when logs are disabled
  digitalWrite(PIN_LED, HIGH);
}

/**
   Arduino loop...
*/
void loop() {
  //need to refresh shiftr API in order to send and receive new messages
  shiftrConnector.loop();

  boolean pressed = debounce();
  if (pressed == true) {
    counter++;
    sendCounter();
    logCounter();
  }

}

/**
   Send the counter to the IoT platforms
*/
void sendCounter() {
  thingspeakSender.sendCounter(counter);
  shiftrConnector.sendCounter(counter);
}

/**
   Logs counter information on Serial Console
*/
void logCounter() {
  logger->log("Button pressed ");
  logger->log((String) counter);
  logger->log("times \n");
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

