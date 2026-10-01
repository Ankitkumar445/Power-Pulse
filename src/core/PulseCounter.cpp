#include "core/PulseCounter.h"

PulseCounter::PulseCounter()
    : count(0) {
}

void PulseCounter::addPulse(const Pulse& pulse) {
    count++;
}

unsigned long PulseCounter::getCount() const {
    return count;
}