#ifndef __THINSPEAK_RECEIVER_H__
#define __THINSPEAK_RECEIVER_H__

class ThingspeakReceiver {

  public :
    unsigned long channelNumber = 204611;
    const char * readAPIKey = "YOUR_API_KEY";

    int receiveCounter();

    void init();

    //default constructor
    ThingspeakReceiver(){};
};

#endif

