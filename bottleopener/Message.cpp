#include "message.h"
#include "logger.h"


#define MESSAGE_JSON_SIZE (JSON_OBJECT_SIZE(3))

Message::Message(const char* sender, const char* platform, int quantity)
{
  this->sender = sender;
  this->platform = platform;
  this->quantity = quantity;
}

bool Message::deserialize(Message& data, char* json)
{
  StaticJsonBuffer<MESSAGE_JSON_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  data.sender = root["sender"];
  data.platform = root["platform"];
  data.quantity = root["quantity"];
  return root.success();
}

void Message::serialize(const Message& data, char* json, size_t maxSize)
{
  StaticJsonBuffer<MESSAGE_JSON_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["sender"] = data.sender;
  root["platform"] = data.platform;
  root["quantity"] = data.quantity;
  root.printTo(json, maxSize);
}

