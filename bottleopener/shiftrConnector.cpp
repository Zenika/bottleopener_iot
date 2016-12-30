#include "shiftrConnector.h"

#include "message.h"

#include "logger.h"
#include "secretKeys.h"

/**
   Only necessary for Shiftr.io API
*/
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  logger->log("Receiving from Shiftr.io...\n");
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

void ShiftrConnector::sendMessage(const char* sender, int counter)
{
  logger->log("Sending to Shiftr...\n");
  
  char buf[128];
  
  Message msg(sender, "Shiftr", counter);
  Message::serialize(msg, buf, 128);
  
  client.publish(SHIFTR_NAMESPACE, buf);
}
