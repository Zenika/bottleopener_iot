#include "shiftrConnector.h"

#include "logger.h"
#include "secretKeys.h"

/**
   Only necessary for Shiftr.io API
*/

int ShiftrConnector::message = 0;
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  logger->log("Receiving from Shiftr.io ...\n");

  int v = payload.toInt();

  ShiftrConnector::message = v;
}

void ShiftrConnector::init()
{
  client.begin("broker.shiftr.io");

  this->connect();

  client.subscribe(SHIFTR_NAMESPACE);
  // client.unsubscribe(SHIFTR_NAMESPACE);

}

void ShiftrConnector::connect() {
  logger->log("\nTry to connect to Shiftr ...");

  while (!client.connect("arduino", SHIFTR_DEVICE_LOGIN, SHIFTR_DEVICE_PWD)) {
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

int ShiftrConnector::receiveMessage()
{
  return ShiftrConnector::message;
}

