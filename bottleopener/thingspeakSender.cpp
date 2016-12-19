#include "thingspeakSender.h"

#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#include "BridgeClient.h"
BridgeClient client;


void ThingspeakSender::init()
{
  ThingSpeak.begin(client);
}

void ThingspeakSender::sendCounter(int counter)
{
  //send '1' to the IoT server on the channel
  ThingSpeak.writeField(channelNumber, 1, counter, writeAPIKey);
}
