#pragma once


#include <aws_iot_mqtt.h>
#include <aws_iot_version.h>

class AwsConnector {

  public :
    void sendMessage(const char* sender, int counter);

    void init();

    void loop();

    //default constructor
    AwsConnector() {};

  private :
    int rc = -100; // return value placeholder 

    aws_iot_mqtt_client myClient;

    void connect();
};

