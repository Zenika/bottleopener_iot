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

void ThingspeakSender::sendMessage(String sender, int counter)
{
  logger->log("Sending to ThingSpeak...");
  
  ThingSpeak.setField(1, sender);
  ThingSpeak.setField(2, (int)counter);

  ThingSpeak.writeFields(THINGSPEAK_CHANNEL_NUMBER, THINGSPEAK_WRITE_API_KEY);  
  
  logger->log(" done. \n");
}
