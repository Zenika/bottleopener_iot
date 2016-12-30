#include "thingspeakSender.h"

#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#include "BridgeClient.h"
BridgeClient client;

#include "logger.h"
#include "secretKeys.h"

void ThingspeakSender::init()
{
  logger->log("\nTry to connect to ThingSpeak ...");
  
  ThingSpeak.begin(client);

  logger->log(" Done ! \n");
}

void ThingspeakSender::sendCounter(int counter)
{
  logger->log("Sending to ThingSpeak...\n");
  
  //send '1' to the IoT server on the channel
  ThingSpeak.writeField(THINGSPEAK_CHANNEL_NUMBER, 1, counter, THINGSPEAK_WRITE_API_KEY);
}
