#pragma once

#include <Arduino.h>

//comment following line to disable Console log and be able to run application without it
//#define LOG_TO_CONSOLE  1

class Logger {
  public :
    
    void init();
    void log(String text);

    Logger() {};
};

extern Logger *logger;
