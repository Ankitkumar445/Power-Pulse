#include <iostream>

#include "core/Pulse.h"
#include "core/PulseCounter.h"
#include "core/AnalyticsAgent.h"

int main() {

    PulseCounter counter;
    AnalyticsAgent analytics;

    Pulse p1(1000);
    Pulse p2(2000);
    Pulse p3(3000);

    counter.addPulse(p1);
    analytics.analyze(p1.getTimestamp());

    counter.addPulse(p2);
    analytics.analyze(p2.getTimestamp());

    counter.addPulse(p3);
    analytics.analyze(p3.getTimestamp());

    if (counter.getCount() == 3 &&
        analytics.getPeakRate() == 1) {

        std::cout << "TEST PASSED" << std::endl;
        return 0;
    }

    std::cout << "TEST FAILED" << std::endl;
    return 1;
}