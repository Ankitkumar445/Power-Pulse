#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

class SignalHandler {
private:
    static volatile bool running;

public:
    static void setup();
    static bool isRunning();
};

#endif