#pragma once

//https://github.com/256dpi/arduino-mqtt
#include <YunMQTTClient.h>

#include "message.h"

class ShiftrConnector {
  public :
    static Message message;

    Message receiveMessage();

    void init();
    void loop();

    //default constructor
    ShiftrConnector() {};

  private :
    YunMQTTClient client;

    void connect();
};

