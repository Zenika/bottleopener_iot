#pragma once

#include <Arduino.h>

class ThingspeakSender {
    
  public :
    void sendMessage(String sender, int counter);

    void init();

    //default constructor
    ThingspeakSender() {};
};

