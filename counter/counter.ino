#include <Bridge.h>

#include "logger.h"

/////////////////////////////////////////////
// Include of Iot Platform's connectors
#include "thingspeakReceiver.h"
ThingspeakReceiver thingspeakReceiver;
int thingsSpeakCounter = 0;

#include "shiftrConnector.h"
ShiftrConnector shiftrConnector;
int shiftrCounter = 0;
/////////////////////////////////////////////

#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define PIN_LED    13

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  pinMode(PIN_LED, OUTPUT);

  Bridge.begin(); //Yun Bridge
  logger->init();

  // init 7-segments matrix
  matrix.begin(0x70);
  matrix.setBrightness(2);
  displayCounter(0);


  //setup the IoT platforms
  logger->log("Start setup connection with IoT platforms...\n");
  thingspeakReceiver.init();
  shiftrConnector.init();

  //Everything seems to be ok, let's start !
  logger->log("\nBottle Opener up, Let's start to play :) !!!\n");

  //highlight blue led just to prevent everything is OK. Useful when logs are disabled
  digitalWrite(PIN_LED, HIGH);
}

/**
   Arduino Loop
*/
void loop() {
  thingsSpeakCounter = thingspeakReceiver.receiveCounter().quantity;

  //need to refresh shiftr API in order to send and receive new messages
  shiftrConnector.loop();
  shiftrCounter = shiftrConnector.receiveMessage();

  //display whatever counter, they should be the same, independently of the platform
  displayCounter(shiftrCounter);

  delay(10);
}

/**
   Display Counter on è
*/
void displayCounter(int counter) {
  matrix.print(counter);
  matrix.writeDisplay();
}

