#include "SDL_opengl.h"
#include <utils/logger.hpp>
#include <iostream>
#include <SDL.h>

void Logger::logMessage(int logLevel, const std::string &msg, const char *filename, int lineno) {
    std::cout << logLevelToString(logLevel) << ": [" << filename << ":" << lineno << "]: " << msg << std::endl;

    if (logLevel == NG_FATAL) {
        std::cout << "Exiting..." << std::endl;
        SDL_Quit();
        exit(-1);
    }
}

void Logger::logGlError() {
    auto e = glGetError();
    if (e) {
        LOG(NG_ERROR, "OpenGL Error Code: " + std::to_string(e));
    }
}

std::string Logger::logLevelToString(int logLevel) {
    switch (logLevel) {
        case NG_DEBUG:
            return "DEBUG";
            break;
        case NG_INFO:
            return "INFO";
            break;
        case NG_WARN:
            return "WARN";
            break;
        case NG_ERROR:
            return "ERROR";
            break;
        case NG_FATAL:
            return "FATAL ERROR";
            break;
    }

    return "NONE";
}
