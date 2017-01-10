#include "initialStateConnector.h"

#ifdef __PLATFORM_INITIALSTATE__
#include <Process.h>

#include "logger.h"
#include "secretKeys.h"

#endif

void InitialStateConnector::init()
{
#ifdef __PLATFORM_INITIALSTATE__
  logger->log("\nTry to connect to InitialState ... done \n");
#endif
}

void InitialStateConnector::sendMessage(String sender, int counter)
{
#ifdef __PLATFORM_INITIALSTATE__

  signalData[0] = sender;
  signalData[1] = counter;

  logger->log("Sending to InitialState...");
  Process isstreamer;

  isstreamer.begin("curl");
  isstreamer.addParameter("-k");
  isstreamer.addParameter("-v");
  isstreamer.addParameter("-X");
  isstreamer.addParameter("POST");
  isstreamer.addParameter("-H");
  isstreamer.addParameter("Content-Type:application/json");
  isstreamer.addParameter("-H");
  isstreamer.addParameter("Accept-Version:0.0.1");

  // IS Access Key Header
  isstreamer.addParameter("-H");
  //isstreamer.addParameter("X-IS-AccessKey:" + INITIALSTATE_ACCESS_KEY);
  isstreamer.addParameter("X-IS-AccessKey:EKyGtR2CN4ksxUmjCbLaPyiQsIvvo003");

  // IS Bucket Key Header
  // Note that bucketName is not needed here
  isstreamer.addParameter("-H");
  //isstreamer.addParameter("X-IS-BucketKey:" + INITIALSTATE_BUCKET_KEY);
  isstreamer.addParameter("X-IS-BucketKey:U7VXH3PEFXAX");

  isstreamer.addParameter("-d");

  // Initialize a string to hold our signal data
  String jsonData;

  jsonData = "[";

  for (int i = 0; i < IS_NUM_SIGNALS; i++)
  {
    jsonData += "{\"key\": \"" + signalName[i] + "\", \"value\": \"" + signalData[i] + "\"}";

    if (i != IS_NUM_SIGNALS - 1)
    {
      jsonData += ",";
    }
  }

  jsonData += "]";

  isstreamer.addParameter(jsonData);

  isstreamer.addParameter("https://groker.initialstate.com/api/events");

  // Print posted data for debug
  Serial.print("Sending data: ");
  Serial.println(jsonData);

  // Run the process
  isstreamer.run();

  logger->log(" done \n");
#endif
}
