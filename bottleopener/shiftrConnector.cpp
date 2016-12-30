#include "shiftrConnector.h"

#include "logger.h"

void ShiftrConnector::init(const char* deviceLogin, const char* pwd)
{
  client.begin("broker.shiftr.io");

  this->deviceLogin = deviceLogin;
  this->pwd = pwd;

  this->connect();

  client.subscribe("/bottle-openner");
  // client.unsubscribe("/bottle-openner");

}

void ShiftrConnector::connect() {
  logger->log("\nTry to connect to Shiftr ...");

  while (!client.connect("arduino", this->deviceLogin, this->pwd)) {
    logger->log(".");
    delay(50);
  }

  logger->log(" Done ! \n");
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
  logger->log("Sending to Shiftr...\n");
  
  char buf[5];
  itoa(counter, buf, 10);
  
  client.publish("/bottle-openner", buf);
}
