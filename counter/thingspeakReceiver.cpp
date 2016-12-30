#include "thingspeakReceiver.h"

#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#include "BridgeClient.h"
BridgeClient client;

#include "message.h"

#include "logger.h"
#include "secretKeys.h"

void ThingspeakReceiver::init()
{
  logger->log("\nTry to connect to ThingSpeak ...");
  
  ThingSpeak.begin(client);
  
  logger->log(" Done ! \n");
}

Message ThingspeakReceiver::receiveCounter()
{
  //logger->log("Receiving from ThingSpeak...\n");
  
  Message msg;
  
  msg.sender = ThingSpeak.readStringField(THINGSPEAK_CHANNEL_NUMBER, 1, THINGSPEAK_READ_API_KEY);
  msg.platform = ThingSpeak.readStringField(THINGSPEAK_CHANNEL_NUMBER, 2, THINGSPEAK_READ_API_KEY);
  msg.quantity = ThingSpeak.readStringField(THINGSPEAK_CHANNEL_NUMBER, 3, THINGSPEAK_READ_API_KEY);

  return msg;
}
