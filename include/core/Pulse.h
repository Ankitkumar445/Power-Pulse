#ifndef PULSE_H
#define PULSE_H

class Pulse {
private:
    unsigned long timestamp;

public:
    Pulse(unsigned long timestamp);

    unsigned long getTimestamp() const;
};

#endif