#include "system/SignalHandler.h"

#include <csignal>

volatile bool SignalHandler::running = true;

void SignalHandler::setup() {

    signal(SIGINT, [](int) {
        SignalHandler::running = false;
    });

    signal(SIGTERM, [](int) {
        SignalHandler::running = false;
    });
}

bool SignalHandler::isRunning() {
    return running;
}