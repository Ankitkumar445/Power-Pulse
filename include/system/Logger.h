#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
private:
    int fileDescriptor;

public:
    Logger(const std::string& filePath);
    ~Logger();

    void log(const std::string& message);
};

#endif