#include "carriotsConnector.h"

#ifdef __PLATFORM_CARRIOTS__

#include <Arduino.h>
#include <Process.h>

#include "logger.h"
#include "secretKeys.h"

#endif

void CarriotsConnector::init()
{
#ifdef __PLATFORM_CARRIOTS__
  logger->log("\nTry to connect to Carriots ... done \n");
#endif
}

void CarriotsConnector::sendMessage(String sender, int counter)
{
#ifdef __PLATFORM_CARRIOTS__
  logger->log("Sending to Carriots...");

  String msg[2][2] = {{"sender", sender}, {"quantity", (String)counter}};
  logger->log(this->carriotsSender.send(msg, 2, CARRIOTS_APIKEY, CARRIOTS_DEVICEKEY));

  logger->log(" done \n");
#endif
}
