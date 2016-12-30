#include "thingspeakReceiver.h"

#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#include "BridgeClient.h"
BridgeClient client;

#include "logger.h"
#include "secretKeys.h"

void ThingspeakReceiver::init()
{
  logger->log("\nTry to connect to ThingSpeak ...");
  
  ThingSpeak.begin(client);
  
  logger->log(" Done ! \n");
}

int ThingspeakReceiver::receiveCounter()
{
  logger->log("Receiving from ThingSpeak...\n");
  
  return ThingSpeak.readIntField(THINGSPEAK_CHANNEL_NUMBER, 1, THINGSPEAK_READ_API_KEY);
}
