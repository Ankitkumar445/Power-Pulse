#include "sources/SimulatedPulseSource.h"

SimulatedPulseSource::SimulatedPulseSource()
    : currentTime(0) {
}

Pulse SimulatedPulseSource::generatePulse() {
    currentTime += 1000;

    return Pulse(currentTime);
}