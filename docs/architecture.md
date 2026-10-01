# PowerPulse Architecture

## 1. System Overview

PowerPulse is a Linux-based smart-meter pulse monitoring and analytics
application developed using C++ and Linux system programming concepts.

The system receives simulated meter pulses, transfers them between
processes using IPC, processes the pulses, counts them, calculates the
pulse rate, and records the results in a Linux log file.

## 2. Architecture

```text
              PULSE SOURCE
                   |
                   v
        SimulatedPulseSource
                   |
                   v
            PARENT PROCESS
                   |
                   |  Pipe IPC
                   v
             CHILD PROCESS
                   |
        +----------+----------+
        |          |          |
        v          v          v
   PulseProcessor  PulseCounter  AnalyticsAgent
        |          |          |
        +----------+----------+
                   |
                   v
                Logger
                   |
                   v
             pulse.log