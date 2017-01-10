#include "shiftrConnector.h"

#include "message.h"

#include "logger.h"
#include "secretKeys.h"

/**
    Only necessary for AWS IoT SDK
**/
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  logger->log("Receiving from AWS IoT...\n");
}

void AwsConnector::init()
{
  client.begin("broker.shiftr.io");

  this->connect();

  client.subscribe(SHIFTR_NAMESPACE);
  // client.unsubscribe(SHIFTR_NAMESPACE);

}

void AwsConnector::connect() {
  logger->log("\nTry to connect to Shiftr ...");

  while (!client.connect("arduino", SHIFTR_DEVICE_LOGIN, SHIFTR_DEVICE_PWD)) {
    logger->log(".");
    delay(50);
  }

  logger->log(" Done ! \n");
}

void AwsConnector::loop()
{
  client.loop();

  if (!client.connected()) {
    connect();
  }
}

void AwsConnector::sendMessage(const char* sender, int counter)
{
  logger->log("Sending to Shiftr...\n");
  
  char buf[128];
  
  Message msg(sender, "Shiftr", counter);
  Message::serialize(msg, buf, 128);
  
  client.publish(SHIFTR_NAMESPACE, buf);
}
