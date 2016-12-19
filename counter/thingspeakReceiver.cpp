#include "thingspeakReceiver.h"

#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#include "BridgeClient.h"
BridgeClient client;


void ThingspeakReceiver::init()
{
  ThingSpeak.begin(client);
}

int ThingspeakReceiver::receiveCounter()
{
  return ThingSpeak.readIntField(channelNumber, 1, readAPIKey);
}
