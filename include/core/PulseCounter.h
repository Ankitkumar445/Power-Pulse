#ifndef PULSE_COUNTER_H
#define PULSE_COUNTER_H

#include "core/Pulse.h"

class PulseCounter {
private:
    unsigned long count;

public:
    PulseCounter();

    void addPulse(const Pulse& pulse);

    unsigned long getCount() const;
};

#endif