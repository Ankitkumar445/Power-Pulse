#include "core/Pulse.h"

Pulse::Pulse(unsigned long timestamp)
    : timestamp(timestamp) {
}

unsigned long Pulse::getTimestamp() const {
    return timestamp;
}