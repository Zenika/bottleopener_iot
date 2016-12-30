#include "shiftrConnector.h"

#include "logger.h"
#include "secretKeys.h"

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

void ShiftrConnector::sendCounter(int counter)
{
  logger->log("Sending to Shiftr...\n");
  
  char buf[5];
  itoa(counter, buf, 10);
  
  client.publish(SHIFTR_NAMESPACE, buf);
}
