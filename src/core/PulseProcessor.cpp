#include "core/PulseProcessor.h"
#include <iostream>

void PulseProcessor::processPulse(const Pulse& pulse) {
    std::cout << "Processing pulse at "
              << pulse.getTimestamp()
              << " ms"
              << std::endl;
}