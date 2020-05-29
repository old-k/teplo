#pragma once 

#include <WString.h>
#include "defs.h"

class Logger;
extern Logger LOGGER;

class Logger {
    private:
        void print(const String& msg);
        void println(const String& msg);

        static const char logLevel = LOG_LEVEL;

    public:
        Logger();
        void error(const String& msg);
        void warning(const String& msg);
        void info(const String& msg);
        void debug(const String& msg);

};

