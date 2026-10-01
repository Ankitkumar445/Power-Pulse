cd /workspace

cat > docs/PRD.md <<'EOF'
# PowerPulse — Product Requirements Document

## 1. Project Overview

**Project Name:** PowerPulse — Smart Meter Pulse Counter & Analytics Agent

**Project Type:** Individual Linux System Programming and C++ Project

**Primary Technologies:**
- C++
- Linux
- Linux system calls
- Process management
- Pipe IPC
- Linux signals
- CMake
- Linux device-driver concepts

## 2. Problem Statement

Smart meters can represent energy consumption events as electrical pulses.
A monitoring system needs to receive these pulse events, count them, process
their timing, calculate basic pulse-rate information, and maintain a record
of the received events.

PowerPulse provides a software-based prototype of this monitoring workflow
using Linux system programming and C++.

## 3. Objective

The objectives of PowerPulse are:

1. Generate simulated meter pulses.
2. Transfer pulse information between Linux processes.
3. Process and count received pulses.
4. Calculate the pulse rate from pulse timestamps.
5. Handle graceful program termination using Linux signals.
6. Store processed pulse events in a Linux log file.
7. Demonstrate C++ object-oriented programming.
8. Demonstrate relevant Linux device-driver architecture concepts.

## 4. Project Scope

### In Scope

- Simulated pulse generation
- Parent and child Linux processes
- Pipe-based IPC
- Pulse processing
- Pulse counting
- Pulse-rate analytics
- Linux signal handling
- File-based logging using Linux system calls
- C++ classes and object-oriented design
- Unit testing
- CMake-based build
- Linux character-device driver skeleton

### Out of Scope

- Real smart-meter hardware integration
- Cloud services
- Database storage
- Web frontend
- Mobile application
- AI/ML processing
- Production-ready kernel driver
- Network communication

## 5. Functional Requirements

### FR-01: Pulse Generation

The system shall generate simulated pulse events at regular intervals.

### FR-02: Inter-Process Communication

The system shall transfer pulse timestamp information from the parent
process to the child process using a Linux pipe.

### FR-03: Pulse Processing

The child process shall convert received timestamp data into a Pulse object
and process the event.

### FR-04: Pulse Counting

The system shall maintain the total number of received pulses.

### FR-05: Analytics

The system shall calculate the pulse rate using the interval between
successive pulse timestamps.

### FR-06: Logging

The system shall write processed pulse events to `logs/pulse.log`.

### FR-07: Graceful Shutdown

The system shall respond to `SIGINT` and `SIGTERM` and terminate the pulse
generation loop gracefully.

### FR-08: Testing

The project shall provide a unit test for pulse counting and analytics.

### FR-09: Driver Architecture

The project shall include a Linux kernel-module source demonstrating
relevant character-device driver concepts.

## 6. Non-Functional Requirements

### NFR-01: Platform

The application shall execute in a Linux environment.

### NFR-02: Language

The application source shall use C++.

The Linux driver source shall use C as required by the Linux kernel module
interface.

No Python, Java, JavaScript, or web framework is required by the project.

### NFR-03: Maintainability

The project shall separate interfaces, implementations, tests, driver code,
and documentation into dedicated directories.

### NFR-04: Reliability

The application shall handle normal termination and close resources such as
pipe file descriptors and log files.

### NFR-05: Testability

Core pulse-counting and analytics functionality shall be independently
testable.

### NFR-06: Documentation

The project shall contain execution instructions, architecture documentation,
driver documentation, and project requirements.

## 7. System Modules

| Module | Responsibility |
|---|---|
| SimulatedPulseSource | Generates simulated pulse timestamps |
| Pulse | Represents one pulse event |
| PulseProcessor | Processes received pulse events |
| PulseCounter | Maintains total pulse count |
| AnalyticsAgent | Calculates pulse-rate information |
| Logger | Writes pulse events to the Linux log file |
| SignalHandler | Handles SIGINT and SIGTERM |
| Main Process | Creates processes and manages pipe communication |
| Driver Layer | Demonstrates Linux character-device driver architecture |

## 8. System Flow

```text
Simulated Pulse Source
        |
        v
Parent Process
        |
        | Pipe IPC
        v
Child Process
        |
        +----> PulseProcessor
        |
        +----> PulseCounter
        |
        +----> AnalyticsAgent
        |
        v
Logger
        |
        v
logs/pulse.log