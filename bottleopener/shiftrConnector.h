#pragma once

#include "platforms.h"

#include <Arduino.h>

#ifdef __PLATFORM_SHIFTR__
//https://github.com/256dpi/arduino-mqtt
#include <YunMQTTClient.h>
#endif

class ShiftrConnector {

  public :
    void sendMessage(String sender, int counter);

    void init();

    void loop();

    //default constructor
    ShiftrConnector() {};

  private :
#ifdef __PLATFORM_SHIFTR__
    YunMQTTClient client;

    void connect();
#endif
};

