#ifndef PULSE_SOURCE_H
#define PULSE_SOURCE_H

#include "core/Pulse.h"

class PulseSource {
public:
    virtual Pulse generatePulse() = 0;

    virtual ~PulseSource() = default;
};

#endif