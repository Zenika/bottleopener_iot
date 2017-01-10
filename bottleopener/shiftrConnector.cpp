#include "shiftrConnector.h"


#include <Arduino.h>

//#include "message.h"

#include "logger.h"
#include "secretKeys.h"

/**
   Only necessary for Shiftr.io API
*/
#ifdef __PLATFORM_SHIFTR__
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  logger->log("Receiving from Shiftr.io...");
  logger->log(" done. \n");
}
#endif

void ShiftrConnector::init()
{
#ifdef __PLATFORM_SHIFTR__
  client.begin("broker.shiftr.io");

  this->connect();

  client.subscribe(SHIFTR_NAMESPACE);
  // client.unsubscribe(SHIFTR_NAMESPACE);
#endif
}

void ShiftrConnector::connect() {
#ifdef __PLATFORM_SHIFTR__
  logger->log("\nTry to connect to Shiftr ...");

  while (!client.connect("arduino", SHIFTR_DEVICE_LOGIN, SHIFTR_DEVICE_PWD)) {
    logger->log(".");
    delay(50);
  }

  logger->log(" Done ! \n");
#endif
}

void ShiftrConnector::loop()
{
#ifdef __PLATFORM_SHIFTR__
  client.loop();

  if (!client.connected()) {
    connect();
  }
#endif
}

void ShiftrConnector::sendMessage(String sender, int counter)
{
#ifdef __PLATFORM_SHIFTR__
  logger->log("Sending to Shiftr...");

  //char buf[128];
  //Message msg(sender, counter);
  //Message::serialize(msg, buf, 128);

  String msg = "{\"sender\" : \"" + sender + "\", \"quantity\" : " + String(counter) + "}";

  client.publish(SHIFTR_NAMESPACE, msg);
  logger->log(" done. \n");
#endif
}
