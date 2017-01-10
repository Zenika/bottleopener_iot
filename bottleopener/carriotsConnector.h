#pragma once

//#define __PLATFORM_CARRIOTS__ 1

#include <Process.h>
#include "SendCarriotsYun.h"

class CarriotsConnector {

  public :
    void sendMessage(String sender, int counter);

    void init();

    //default constructor
    CarriotsConnector() {};

  private:
    SendCarriotsYun carriotsSender;
};

