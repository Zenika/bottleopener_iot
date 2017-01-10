#pragma once

#define __PLATFORM_INITIALSTATE__ 1

#include <Arduino.h>

#define IS_NUM_SIGNALS  2

class InitialStateConnector {

  public :
    void sendMessage(String sender, int counter);

    void init();

    //default constructor
    InitialStateConnector() {};
    
  private:
    String signalName[IS_NUM_SIGNALS] = {"sender", "quantity"};
    String signalData[IS_NUM_SIGNALS];
};

