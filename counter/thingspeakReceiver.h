#pragma once

#include "message.h"

class ThingspeakReceiver {

  public :
    Message receiveMessage();

    void init();

    //default constructor
    ThingspeakReceiver() {};
};

