#pragma once

#include "platforms.h"

#include <Arduino.h>

#ifdef __PLATFORM_CARRIOTS__
#include <Process.h>
#include "SendCarriotsYun.h"
#endif

class CarriotsConnector {

  public :
    void sendMessage(String sender, int counter);

    void init();

    //default constructor
    CarriotsConnector() {};

#ifdef __PLATFORM_CARRIOTS__
  private:
    SendCarriotsYun carriotsSender;
#endif
};

