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

  /*
     Header :
    POST /streams/ HTTP/1.1
    Host: api.carriots.com
    Accept: application/json
    User-Agent: defaultDevice@gbuchet.gbuchet
    Content-Type: application/json
    Content-Length: 177
    carriots.apikey: 5887cec49fa3ce1876baafd4b9836d01d170cdbd22510027f7213ef37c0f1792
  */
  /*
     Body :
    {
    "protocol": "v2",
    "checksum": "",
    "device": "defaultDevice@gbuchet.gbuchet",
    "at": "now",
    "data": {
        "sender": "Gwen",
        "quantity": 3
    }
    }
  */

  Process isbucket;

  isbucket.begin("curl");
  isbucket.addParameter("-k");
  isbucket.addParameter("-v");
  isbucket.addParameter("-X");
  isbucket.addParameter("POST /streams/ HTTP/1.1");
  isbucket.addParameter("Host: api.carriots.com");
  isbucket.addParameter("Accept: application/json");
  isbucket.addParameter("User-Agent: defaultDevice@gbuchet.gbuchet");
  isbucket.addParameter("Content-Type:application/json");
  isbucket.addParameter("carriots.apikey: 5887cec49fa3ce1876baafd4b9836d01d170cdbd22510027f7213ef37c0f1792");

  // IS Bucket Key Header
  isbucket.addParameter("-d");
  isbucket.addParameter("{\"protocol\": \"v1\",\"device\": \"defaultDevice@gbuchet.gbuchet\",\"at\": \"now\",\"persist\": \"true\",\"data\": {\"name\": \"Cunegonde\"}}");

  // Run the process
  isbucket.run();


  //String msg[2][2] = {{"sender", sender}, {"quantity", (String)counter}};
  //this->carriotsSender.send(msg, 2, CARRIOTS_APIKEY, CARRIOTS_DEVICEKEY);


  String dataString = "{\"protocol\": \"v1\",\"device\": \"defaultDevice@gbuchet.gbuchet\",\"at\": \"now\",\"persist\": \"true\",\"data\": {\"name\": \"Robert\"}}";

  // form the string for the APIKEY header parameter:
  /* String apiString = "carriots.apikey: ";
    apiString += CARRIOTS_APIKEY;

    // Send the HTTP POST request
    Process carriots;
    Serial.print("Sending data... ");
    carriots.begin("curl");
    carriots.addParameter("-k");
    carriots.addParameter("--request");
    carriots.addParameter("POST");
    carriots.addParameter("--data");
    carriots.addParameter(dataString);
    carriots.addParameter("--header");
    carriots.addParameter(apiString);
    carriots.addParameter("https://api.carriots.com/streams/");
    carriots.run();
    Serial.println("done!");

    // If there's incoming data from the net connection,
    // send it out the Serial:
    while (carriots.available() > 0) {
     char c = carriots.read();
     Serial.write(c);
    }*/


  logger->log(" done \n");
#endif
}
