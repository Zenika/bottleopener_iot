#pragma once

class ThingspeakSender {
    
  public :
    void sendMessage(const char* sender, int counter);

    void init();

    //default constructor
    ThingspeakSender() {};
};

