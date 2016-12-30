#pragma once

//https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>

class Message
{
  public :

    //name of the bottle-opener
    const char* sender;
    //name of the IoT platform to send the message to
    const char* platform;
    //quantity of bottle opened (should always be 1, as we open 1 bottle at a time)
    int quantity;

    static bool deserialize(Message& data, char* json);
    static void serialize(const Message& data, char* json, size_t maxSize);

    Message() {}
    Message(const char* sender, const char* platform, int quantity);
};


