#ifndef __SHIFTR_CONNECTOR_H__
#define __SHIFTR_CONNECTOR_H__

#include <YunMQTTClient.h>

class ShiftrConnector {

  public :
    void sendCounter(int counter);

    void init(const char* deviceLogin, const char* pwd);

    void loop();

    //default constructor
    ShiftrConnector() {};

  private :
    YunMQTTClient client;
    const char* deviceLogin;
    const char* pwd;

    void connect();
};

#endif

