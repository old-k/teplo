#include <stdio.h>
#include <WString.h>
#include <Arduino.h>
#include "Logger.hpp"

Logger LOGGER;

//------------------------------------------------------------------------------

Logger::Logger() {
}
//------------------------------------------------------------------------------
void Logger::println(const String& msg) {
#ifdef CON_DEBUG
    Serial.println(msg);
#endif
}
//------------------------------------------------------------------------------
void Logger::print(const String& msg) {
#ifdef CON_DEBUG
    Serial.print(msg);
#endif
}
//------------------------------------------------------------------------------
void Logger::error(const String& msg) {
    if (logLevel <= LOG_LEVEL_ERROR) {
        println("ERROR: " + msg);
    }
}
//------------------------------------------------------------------------------
void Logger::warning(const String& msg) {
    if (logLevel <= LOG_LEVEL_WARNING) {
        println("WARN: " + msg);
    }
}
//------------------------------------------------------------------------------
void Logger::info(const String& msg) {
    if (logLevel <= LOG_LEVEL_INFO) {
        println("INFO: " + msg);
    }
}
//------------------------------------------------------------------------------
void Logger::debug(const String& msg) {
    if (logLevel <= LOG_LEVEL_DEBUG) {
        println("DBG: " + msg);
    }
}