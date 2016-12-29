#include "shiftrConnector.h"

#include <Bridge.h>

void ShiftrConnector::init(const char* deviceLogin, const char* pwd)
{
  client.begin("broker.shiftr.io");

  this->deviceLogin = deviceLogin;
  this->pwd = pwd;

  connect();

  client.subscribe("/bottle-openner");
  // client.unsubscribe("/bottle-openner");

}

void ShiftrConnector::connect() {
  while (!client.connect("arduino", this->deviceLogin, this->pwd)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nBottle-Opener is now connected to Shiftr!");
}

void ShiftrConnector::loop()
{
  client.loop();

  if (!client.connected()) {
    connect();
  }
}

void ShiftrConnector::sendCounter(int counter)
{
  char buf[5];
  itoa(counter, buf, 10);
  
  client.publish("/bottle-openner", buf);
}
