#ifndef SIMULATED_PULSE_SOURCE_H
#define SIMULATED_PULSE_SOURCE_H

#include "sources/PulseSource.h"

class SimulatedPulseSource : public PulseSource {
private:
    unsigned long currentTime;

public:
    SimulatedPulseSource();

    Pulse generatePulse() override;
};

#endif