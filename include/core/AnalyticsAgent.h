#ifndef ANALYTICS_AGENT_H
#define ANALYTICS_AGENT_H

class AnalyticsAgent {
private:
    unsigned long totalPulses;
    unsigned long previousTimestamp;
    unsigned long peakRate;

public:
    AnalyticsAgent();

    void analyze(unsigned long timestamp);

    unsigned long getTotalPulses() const;
    unsigned long getPeakRate() const;
};

#endif