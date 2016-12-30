#include "shiftrConnector.h"

#include "logger.h"

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
    logger->log(".");
    delay(500);
  }

  logger->log("\nBottle-Opener is now connected to Shiftr!");
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
