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
char msg[32]; // read-write buffer
int cnt = 0; // loop counts
int rc = -100; // return value placeholder
bool success_connect = false; // whether it is connected
int ledPin = 8; // LED connected to digital pin 13
int inPin = 4;   // pushbutton connected to digital pin 7
int val = LOW;     // variable to store the read value


// Basic callback function that prints out the message
void msg_callback(char* src, unsigned int len, Message_status_t flag) {
  if (flag == STATUS_NORMAL) {
    Serial.println("Message received");
    char dst[len];
    strcpy(dst, src); /* BANG!!! */
    strncpy(dst, src, len);
    Serial.println(dst);
    int state = 0;
    Serial.println(state);
    if (state == 1) {
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(ledPin, LOW);
    }
  }
}

void setup() {
  // Start Serial for print-out and wait until it's ready
  Serial.begin(9600);
  while (!Serial);
  //
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT);
  digitalWrite(inPin, LOW);
  digitalWrite(ledPin, LOW);
  char curr_version[80];
  snprintf_P(curr_version, 80, PSTR("AWS IoT SDK Version(dev) %d.%d.%d-%s\n"), VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);
  Serial.println(curr_version);
  // Set up the client
  Serial.println(AWS_IOT_MY_THING_NAME);
  if ((rc = myClient.setup("decap")) == 0) {
    // Load user configuration
    if ((rc = myClient.config(AWS_IOT_MQTT_HOST, AWS_IOT_MQTT_PORT, AWS_IOT_ROOT_CA_PATH, AWS_IOT_PRIVATE_KEY_PATH, AWS_IOT_CERTIFICATE_PATH)) == 0) {
      // Use default connect: 60 sec for keepalive
      if ((rc = myClient.connect()) == 0) {
        success_connect = true;
  
        if ((rc = myClient.subscribe("ledState", 1, msg_callback)) != 0) {
          Serial.println("Subscribe failed!");
          Serial.println(rc);
        }
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
}

void loop() {

  if (success_connect) {
    sprintf(msg, "{\"buttonState\": %d }", digitalRead(inPin));
    if ((rc = myClient.publish("beer", msg, strlen(msg), 1, false)) != 0) {
      Serial.println(F("Publish failed!"));
      Serial.println(rc);
    }

    // Get a chance to run a callback
    if ((rc = myClient.yield()) != 0) {
      Serial.println("Yield failed!");
      Serial.println(rc);
    }
    delay(500);
  }
}
