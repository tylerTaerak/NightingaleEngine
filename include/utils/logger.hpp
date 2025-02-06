#pragma once

#define NG_DEBUG 0
#define NG_INFO 1
#define NG_WARN 2
#define NG_ERROR 3
#define NG_FATAL 4

#define LOG(x, msg) Logger::logMessage(x, msg, __FILE__, __LINE__)

#include <string>

class Logger {
    public:
        static void logMessage(int logLevel, const std::string &msg, const char *filename, int lineno);

        static void logGlError();
    private:
        static std::string logLevelToString(int logLevel);
};
