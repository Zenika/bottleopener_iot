#include "thingspeakSender.h"

#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#include "BridgeClient.h"
BridgeClient client;

#include "message.h"

#include "logger.h"
#include "secretKeys.h"

void ThingspeakSender::init()
{
  logger->log("\nTry to connect to ThingSpeak ...");

  ThingSpeak.begin(client);

  logger->log(" Done ! \n");
}

void ThingspeakSender::sendMessage(const char* sender, int counter)
{
  logger->log("Sending to ThingSpeak...\n");

  char buf[128];

  Message msg(sender, "ThingSpeak", counter);
  Message::serialize(msg, buf, 128);
  
  ThingSpeak.setField(1, (String)sender);
  ThingSpeak.setField(2, (int)counter);

  ThingSpeak.writeFields(THINGSPEAK_CHANNEL_NUMBER, THINGSPEAK_WRITE_API_KEY);  
}
