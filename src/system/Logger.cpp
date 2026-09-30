#include "system/Logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>

Logger::Logger(const std::string& filePath) {

    fileDescriptor = open(
        filePath.c_str(),
        O_WRONLY | O_CREAT | O_APPEND,
        0644
    );

    if (fileDescriptor == -1) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

Logger::~Logger() {

    if (fileDescriptor != -1) {
        close(fileDescriptor);
    }
}

void Logger::log(const std::string& message) {

    if (fileDescriptor == -1) {
        return;
    }

    write(
        fileDescriptor,
        message.c_str(),
        message.length()
    );

    write(
        fileDescriptor,
        "\n",
        1
    );
}