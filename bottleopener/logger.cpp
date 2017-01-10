#include "logger.h"

Logger *logger = new Logger();

void Logger::init()
{
#ifdef LOG_TO_CONSOLE
  Serial.begin(9600);
  while (!Serial);
#endif
}

void Logger::log(String text)
{
#ifdef LOG_TO_CONSOLE
  Serial.print(text);
#endif
}

void Logger::log(int text)
{
#ifdef LOG_TO_CONSOLE
  Serial.print(text);
#endif
}

