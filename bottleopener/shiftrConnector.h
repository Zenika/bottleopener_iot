#pragma once

#include <YunMQTTClient.h>

class ShiftrConnector {

  public :
    void sendCounter(int counter);

    void init();

    void loop();

    //default constructor
    ShiftrConnector() {};

  private :
    YunMQTTClient client;

    void connect();
};

