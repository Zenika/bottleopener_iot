/*
   Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License").
   You may not use this file except in compliance with the License.
   A copy of the License is located at

    http://aws.amazon.com/apache2.0

   or in the "license" file accompanying this file. This file is distributed
   on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   express or implied. See the License for the specific language governing
   permissions and limitations under the License.
*/
#include <aws_iot_mqtt.h>
#include <aws_iot_version.h>
#include "aws_iot_config.h"

aws_iot_mqtt_client myClient; // init iot_mqtt_client
char msg[35]; // read-write buffer
int cnt = 0; // loop counts
int rc = -100; // return value placeholder
bool success_connect = false; // whether it is connected
int inPin = 10;   // pushbutton connected to digital pin 7
int val = LOW;     // variable to store the read value
int buttonState = LOW;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  // Start Serial for print-out and wait until it's ready
  Serial.begin(9600);
  while (!Serial);

  //
  Serial.println("Try to connect to AWS IoT ...\n");
  pinMode(inPin, INPUT);
  digitalWrite(inPin, LOW);
  char curr_version[80];
  snprintf_P(curr_version, 80, PSTR("AWS IoT SDK Version(dev) %d.%d.%d-%s\n"), VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);
  Serial.println(curr_version);

  // Set up the client
  if ((rc = myClient.setup("decap")) == 0) {
    // Load user configuration
    if ((rc = myClient.config(AWS_IOT_MQTT_HOST, AWS_IOT_MQTT_PORT, AWS_IOT_ROOT_CA_PATH, AWS_IOT_PRIVATE_KEY_PATH, AWS_IOT_CERTIFICATE_PATH)) == 0) {
      // Use default connect: 60 sec for keepalive
      if ((rc = myClient.connect()) == 0) {
        success_connect = true;
      }
      else {
        Serial.println(F("Connect failed!"));
        Serial.println(rc);
      }
    }
    else {
      Serial.println(F("Config failed!"));
      Serial.println(rc);
    }
  }
  else {
    Serial.println(F("Setup failed!"));
    Serial.println(rc);
  }
  // Delay to make sure SUBACK is received, delay time could vary according to the server
  delay(2000);
  Serial.println("... done \n");
}

boolean debounce() {

  boolean retVal = false;
  int reading = digitalRead(inPin);
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

void logCounter() {
  Serial.print("Button pressed ");
  Serial.print(cnt);
  Serial.print(" times \n");
}

void sendCounter() {
  sprintf(msg, "{\"sender\":\"Adrien\",\"quantity\":%d }", cnt);
  if ((rc = myClient.publish("beer", msg, strlen(msg), 1, false)) != 0) {
    Serial.println(F("Publish failed!"));
    Serial.println(rc);
  }
}

void loop() {

  if (success_connect) {
    boolean pressed = debounce();
    if (pressed == true) {
      cnt++;
      sendCounter();
      logCounter();
    }

    // Get a chance to run a callback
    if ((rc = myClient.yield()) != 0) {
      Serial.println("Yield failed!");
      Serial.println(rc);
    }
  }
}
