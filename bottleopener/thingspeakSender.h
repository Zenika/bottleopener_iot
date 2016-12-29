#ifndef __THINSPEAK_SENDER_H__
#define __THINSPEAK_SENDER_H__

class ThingspeakSender {

  private :
    unsigned long channelNumber = 204611;
    const char * writeAPIKey = "YOUR_API_KEY";
    
  public :
    void sendCounter(int counter);

    void init();

    //default constructor
    ThingspeakSender() {};
};

#endif

