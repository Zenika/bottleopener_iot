#pragma once

#include <Arduino.h>

#define LOG_TO_CONSOLE  1

class Logger {
  public :
    
    void init();
    void log(String text);

    Logger() {};
};

extern Logger *logger;
