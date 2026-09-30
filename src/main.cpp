#include "system/SignalHandler.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>


#include "sources/SimulatedPulseSource.h"
#include "core/PulseCounter.h"
#include "core/PulseProcessor.h"
#include "system/Logger.h"
#include "core/AnalyticsAgent.h"

int main() {

    int pipefd[2];

    if (pipe(pipefd) == -1) {
        std::cerr << "Failed to create pipe." << std::endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Failed to create process." << std::endl;
        return 1;
    }

    // Parent process
if (pid > 0) {

    close(pipefd[0]);

    SignalHandler::setup();

    SimulatedPulseSource source;

    while (SignalHandler::isRunning()) {

        Pulse pulse = source.generatePulse();

        unsigned long timestamp = pulse.getTimestamp();

        write(
            pipefd[1],
            &timestamp,
            sizeof(timestamp)
        );

        std::cout << "Parent: Generated pulse at "
                  << timestamp
                  << " ms"
                  << std::endl;

        usleep(1000000);
    }

    std::cout << "\nParent: Stopping pulse generation..."
              << std::endl;

    close(pipefd[1]);

    wait(nullptr);

    std::cout << "Parent: Child process finished."
              << std::endl;
}

   // Child process
else {

    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

    close(pipefd[1]);

    PulseProcessor processor;
    PulseCounter counter;
    AnalyticsAgent analytics;
    Logger logger("../logs/pulse.log");

    unsigned long timestamp;

    while (
        read(
            pipefd[0],
            &timestamp,
            sizeof(timestamp)
        ) > 0
    ) {

        Pulse pulse(timestamp);

        processor.processPulse(pulse);

        counter.addPulse(pulse);

        analytics.analyze(timestamp);

        std::string message =
            "Child: Pulse received at " +
            std::to_string(timestamp) +
            " ms | Total: " +
            std::to_string(counter.getCount());

        logger.log(message);

        std::cout << message << std::endl;
    }

    close(pipefd[0]);

    std::cout << "Child: Final pulse count = "
              << counter.getCount()
              << std::endl;

    std::cout << "Child: Peak pulse rate = "
              << analytics.getPeakRate()
              << " pulse/sec"
              << std::endl;

    }

    return 0;
}