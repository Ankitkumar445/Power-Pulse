#include "core/AnalyticsAgent.h"

#include <iostream>

AnalyticsAgent::AnalyticsAgent()
    : totalPulses(0),
      previousTimestamp(0),
      peakRate(0) {
}

void AnalyticsAgent::analyze(unsigned long timestamp) {

    totalPulses++;

    if (previousTimestamp != 0) {

        unsigned long interval =
            timestamp - previousTimestamp;

        if (interval > 0) {

            unsigned long rate =
                1000 / interval;

            if (rate > peakRate) {
                peakRate = rate;
            }

            std::cout << "Analytics: "
                      << "Rate = "
                      << rate
                      << " pulse/sec"
                      << std::endl;
        }
    }

    previousTimestamp = timestamp;
}

unsigned long AnalyticsAgent::getTotalPulses() const {
    return totalPulses;
}

unsigned long AnalyticsAgent::getPeakRate() const {
    return peakRate;
}