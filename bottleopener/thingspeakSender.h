#pragma once

//#define __PLATFORM_THINGSPEAK__ 1
#include <Arduino.h>

class ThingspeakSender {
    
  public :
    void sendMessage(String sender, int counter);

    void init();

    //default constructor
    ThingspeakSender() {};
};

