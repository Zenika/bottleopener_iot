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

Message ThingspeakReceiver::receiveMessage()
{
  //logger->log("Receiving from ThingSpeak...\n");

  //String sender = ThingSpeak.readStringField(THINGSPEAK_CHANNEL_NUMBER, 1, THINGSPEAK_READ_API_KEY);
  //String platform = ThingSpeak.readStringField(THINGSPEAK_CHANNEL_NUMBER, 2, THINGSPEAK_READ_API_KEY);
  int quantity = ThingSpeak.readIntField(THINGSPEAK_CHANNEL_NUMBER, 3, THINGSPEAK_READ_API_KEY);

  
  Message msg;

  /*char bufSender[sizeof(sender)];
  sender.toCharArray(bufSender, 128);

  char bufPlatform[sizeof(platform)];
  platform.toCharArray(bufPlatform, 128);
  
  msg.sender = bufSender;
  msg.platform = bufPlatform;*/
  msg.sender = "";
  msg.platform = "";
  msg.quantity = quantity;
  logger->log("Receiving from ThingSpeak : ");
  logger->log(String(msg.quantity));

  return msg;
}
