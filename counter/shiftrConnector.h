#pragma once

//https://github.com/256dpi/arduino-mqtt
#include <YunMQTTClient.h>

class ShiftrConnector {
  public :
    static int message;

    int receiveMessage();

    void init();
    void loop();

    //default constructor
    ShiftrConnector() {};

  private :
    YunMQTTClient client;

    void connect();
};

