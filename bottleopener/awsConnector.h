#pragma once

#define __PLATFORM_AWS__ 1

class AWSConnector
{
  public:
    void init();
    void sendMessage(String sender, int counter);
    
    AWSConnector() {};
}

