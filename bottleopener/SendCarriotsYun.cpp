#include "SendCarriotsYun.h"
#include <Process.h>

String dataString = "";

/**
    Sends an HTTP curl request to the Carriots system after constructing a JSON

    @param array contains the key-value pairs that will be sent in the JSON
    @param elements contains the number of columns in the array
    @param apikey contains the apikey of the Carriots user
    @param device contains the device id of the Carriots user
    @return gives the message sent from the Carriots server
*/

String SendCarriotsYun::send(String array[][2], int elements, String apikey, String device){
  String key;
  String value;
  //Construct the JSON from the array passed to the method
  dataString = "{\"protocol\":\"v2\",\"checksum\":\"\",\"device\":\"";
  dataString += device;
  dataString += "\",\"at\":\"now\",\"data\":{";
  //Run through the bucle add each key-value in the array to the JSON
  for (int i=0; i<elements;i++){
    key=array[i][0];
    value=array[i][1];
    dataString += "\""+key+"\":";
    dataString += "\""+value+"\"";
    if (elements>1 && i!=elements-1){
       dataString += ",";
    }
  }
  dataString += "}}";
  Serial.println("\n\nDataString:\n"+dataString);

  //Form the string for the APIKEY header parameter:
  String apiString = "carriots.apikey: ";
  apiString += apikey;
  //Send the HTTP POST request
  Process carriots;
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

  //Store incoming data from the net connection to send back to the sketch
  String msg;
  /*while (carriots.available() > 0) {
    char c = carriots.read();
    msg += c;
  }*/
  return msg;
}
