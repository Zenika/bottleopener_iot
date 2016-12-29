#ifndef __THINSPEAK_RECEIVER_H__
#define __THINSPEAK_RECEIVER_H__

class ThingspeakReceiver {

  private :
    unsigned long channelNumber = 204611;
    const char * readAPIKey = "YOUR_API_KEY";

  public :
    int receiveCounter();

    void init();

    //default constructor
    ThingspeakReceiver() {};
};

#endif

