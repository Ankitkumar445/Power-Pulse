# ⚡ PowerPulse

## Smart Energy Meter Pulse Counter & Analytics Agent

<p align="center">
  <strong>A Linux-based C++ system-programming project that simulates smart-meter pulses, transfers them between processes using IPC, performs pulse analytics, and records monitoring data.</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/C-Linux%20Driver-orange?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Linux-System%20Programming-black?style=for-the-badge&logo=linux" />
  <img src="https://img.shields.io/badge/CMake-Build-red?style=for-the-badge&logo=cmake" />
  <img src="https://img.shields.io/badge/GNU%20Make-Build-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Git-Version%20Control-black?style=for-the-badge&logo=git" />
</p>

---

# 📌 Overview

**PowerPulse** is a software-based smart-meter pulse monitoring prototype
implemented using **C++ and Linux system programming concepts**.

A smart energy meter can represent energy-consumption events as electrical
pulses. PowerPulse simulates these pulse events and demonstrates how a
Linux-based monitoring system can receive, transfer, process, count, analyze,
and log them.

The application uses a **parent-child process architecture**. The parent
process generates simulated pulse timestamps and sends them to the child
process through a **Linux pipe**. The child process receives the timestamps,
creates pulse objects, processes the events, maintains the pulse count,
calculates pulse-rate information, and records the results in a log file.

The project also contains a **Linux character-device driver skeleton** to
demonstrate the kernel-side architecture and lifecycle of a pulse-monitoring
system.

---

# 🎯 Project Objective

The primary objective of PowerPulse is to demonstrate how a smart-meter
pulse-monitoring pipeline can be designed using:

* C++ Object-Oriented Programming
* Linux processes
* Inter-Process Communication
* Linux system calls
* File descriptors
* Signal handling
* Modular software architecture
* Basic real-time event analytics
* Linux logging
* Unit testing
* Linux device-driver concepts

The project focuses on **system programming and software architecture**
rather than a web application or database-based monitoring system.

---

# 🧩 Problem Statement

Smart meters can generate a sequence of electrical pulses corresponding to
energy-consumption events.

A monitoring application needs to:

1. Receive pulse events.
2. Transfer pulse information between system components.
3. Process every event reliably.
4. Maintain the total pulse count.
5. Analyze the timing between pulses.
6. Record the processed events.
7. Handle system termination safely.

PowerPulse provides a simplified software implementation of this workflow
using Linux processes and C++.

---

# 🏗️ System Architecture

```text
                    ┌────────────────────────┐
                    │ SimulatedPulseSource   │
                    │                        │
                    │ Generates pulse events │
                    └────────────┬───────────┘
                                 │
                                 ▼
                    ┌────────────────────────┐
                    │    Parent Process      │
                    │                        │
                    │ Generates timestamps   │
                    └────────────┬───────────┘
                                 │
                                 │ write()
                                 │
                                 ▼
                    ╔════════════════════════╗
                    ║      Linux Pipe        ║
                    ║       IPC Channel      ║
                    ╚════════════╤═══════════╝
                                 │
                                 │ read()
                                 ▼
                    ┌────────────────────────┐
                    │     Child Process      │
                    └────────────┬───────────┘
                                 │
             ┌───────────────────┼───────────────────┐
             │                   │                   │
             ▼                   ▼                   ▼
    ┌────────────────┐  ┌────────────────┐  ┌────────────────┐
    │ PulseProcessor │  │  PulseCounter  │  │ AnalyticsAgent │
    │                │  │                │  │                │
    │ Process event  │  │ Count pulses   │  │ Calculate rate │
    └────────────────┘  └────────────────┘  └───────┬────────┘
             │                   │                   │
             └───────────────────┼───────────────────┘
                                 │
                                 ▼
                         ┌───────────────┐
                         │    Logger     │
                         └───────┬───────┘
                                 │
                                 ▼
                         ┌───────────────┐
                         │  pulse.log    │
                         └───────────────┘
```

---

# 🔄 How the System Works

The complete execution flow is:

```text
1. Program starts
       ↓
2. Linux pipe is created
       ↓
3. fork() creates parent and child processes
       ↓
4. Parent generates a simulated pulse
       ↓
5. Parent extracts the pulse timestamp
       ↓
6. Parent writes timestamp into the pipe
       ↓
7. Child reads timestamp from the pipe
       ↓
8. Child creates a Pulse object
       ↓
9. PulseProcessor processes the pulse
       ↓
10. PulseCounter increments the count
       ↓
11. AnalyticsAgent calculates pulse rate
       ↓
12. Logger writes the event to pulse.log
       ↓
13. Parent waits and generates the next pulse
       ↓
14. Process repeats
```

---

# ⚙️ Core Components

## 1. Pulse

Represents one pulse event.

```text
Pulse
 └── timestamp
```

It encapsulates the timestamp associated with a pulse.

---

## 2. PulseSource

`PulseSource` is an abstract interface for pulse generation.

It demonstrates **abstraction and polymorphism**.

```cpp
class PulseSource {
public:
    virtual Pulse generatePulse() = 0;
    virtual ~PulseSource() = default;
};
```

---

## 3. SimulatedPulseSource

`SimulatedPulseSource` inherits from `PulseSource` and generates simulated
pulse timestamps.

```text
PulseSource
     ▲
     │
     │ inheritance
     │
SimulatedPulseSource
```

The current prototype generates one simulated pulse approximately every
second.

---

## 4. PulseProcessor

Responsible for processing each pulse received by the child process.

Example:

```text
Processing pulse at 1000 ms
```

---

## 5. PulseCounter

Maintains the total number of received pulses.

For example:

```text
Pulse 1 → Total: 1
Pulse 2 → Total: 2
Pulse 3 → Total: 3
```

---

## 6. AnalyticsAgent

Analyzes the timing between consecutive pulses.

The current implementation calculates:

```text
Pulse Rate = 1000 / interval
```

where `interval` represents the difference between two pulse timestamps in
milliseconds.

For a 1000 ms interval:

```text
1000 / 1000 = 1 pulse/sec
```

The component also tracks the highest pulse rate observed during execution.

---

## 7. Logger

The logger uses Linux file-descriptor operations to write processed pulse
events to:

```text
logs/pulse.log
```

It uses:

```cpp
open()
write()
close()
```

The file is opened in append mode so previous records are preserved.

---

## 8. SignalHandler

The application handles:

* `SIGINT`
* `SIGTERM`

When the user presses:

```text
Ctrl + C
```

the parent stops generating new pulses, closes the pipe, and waits for the
child process to finish.

---

# 🐧 Linux System Programming Concepts

PowerPulse demonstrates several important Linux system-programming concepts.

| Concept          | Usage                               |
| ---------------- | ----------------------------------- |
| `fork()`         | Creates the child process           |
| `pipe()`         | Creates the IPC channel             |
| `read()`         | Child receives pulse data           |
| `write()`        | Parent sends pulse data             |
| `open()`         | Opens the log file                  |
| `close()`        | Releases file descriptors           |
| `wait()`         | Parent waits for child              |
| `SIGINT`         | Handles Ctrl+C                      |
| `SIGTERM`        | Handles termination                 |
| File descriptors | Used for Linux I/O resources        |
| Processes        | Separate parent and child execution |

---

# 🔌 Inter-Process Communication

PowerPulse uses a **Unix/Linux pipe** for communication.

```text
Parent Process
      |
      | write(timestamp)
      ▼
   ┌─────────┐
   │  PIPE   │
   └─────────┘
      |
      | read(timestamp)
      ▼
Child Process
```

The parent writes the timestamp into the pipe.

The child reads the timestamp from the pipe and continues processing.

This demonstrates one of the fundamental Linux IPC mechanisms.

---

# 🧱 C++ Object-Oriented Design

The project uses a modular object-oriented architecture.

### OOP concepts demonstrated

| OOP Concept   | Implementation                              |
| ------------- | ------------------------------------------- |
| Encapsulation | Private class attributes                    |
| Abstraction   | `PulseSource` abstract class                |
| Inheritance   | `SimulatedPulseSource : public PulseSource` |
| Polymorphism  | Virtual `generatePulse()`                   |
| Constructors  | Object initialization                       |
| Destructors   | Resource cleanup in `Logger`                |
| Composition   | Components operate using `Pulse` objects    |

The project separates interfaces into header files and implementations into
`.cpp` files.

---

# 📂 Project Structure

```text
PowerPulse/
│
├── CMakeLists.txt
├── Makefile
├── Dockerfile
├── README.md
├── .gitignore
│
├── docs/
│   ├── PRD.md
│   ├── architecture.md
│   ├── class-diagram.md
│   ├── driver.md
│   ├── execution.md
│   ├── progress.md
│   ├── sequence-diagram.md
│   └── state-machine.md
│
├── driver/
│   ├── Makefile
│   └── powerpulse_driver.c
│
├── include/
│   ├── core/
│   │   ├── AnalyticsAgent.h
│   │   ├── Pulse.h
│   │   ├── PulseCounter.h
│   │   └── PulseProcessor.h
│   │
│   ├── sources/
│   │   ├── PulseSource.h
│   │   └── SimulatedPulseSource.h
│   │
│   └── system/
│       ├── Logger.h
│       └── SignalHandler.h
│
├── logs/
│   └── pulse.log
│
├── src/
│   ├── core/
│   │   ├── AnalyticsAgent.cpp
│   │   ├── Pulse.cpp
│   │   ├── PulseCounter.cpp
│   │   └── PulseProcessor.cpp
│   │
│   ├── main.cpp
│   │
│   ├── sources/
│   │   └── SimulatedPulseSource.cpp
│   │
│   └── system/
│       ├── Logger.cpp
│       └── SignalHandler.cpp
│
└── tests/
    └── test_pulse.cpp
```

> `build/` is intentionally excluded from Git because it contains generated
> CMake/build artifacts.

---

# 🧪 Testing

The project includes a unit-test executable:

```text
tests/test_pulse.cpp
```

The test verifies:

* Pulse counting
* Pulse-rate analytics

Run:

```bash
cd build
./test_pulse
```

Expected output:

```text
Analytics: Rate = 1 pulse/sec
Analytics: Rate = 1 pulse/sec
TEST PASSED
```

---

# ▶️ Build and Run

## Prerequisites

A Linux environment with:

* C++ compiler
* CMake
* GNU Make

For example:

```bash
g++
cmake
make
```

---

## Build

From the project root:

```bash
mkdir -p build
cd build
cmake ..
make
```

Or use the project Makefile:

```bash
make
```

---

## Run the Application

From the build directory:

```bash
./powerpulse
```

Example:

```text
Parent: Generated pulse at 1000 ms
Processing pulse at 1000 ms
Child: Pulse received at 1000 ms | Total: 1

Parent: Generated pulse at 2000 ms
Processing pulse at 2000 ms
Analytics: Rate = 1 pulse/sec
Child: Pulse received at 2000 ms | Total: 2
```

The application continues generating and processing pulses.

---

# 🛑 Graceful Shutdown

Press:

```text
Ctrl + C
```

The parent process receives `SIGINT`.

The shutdown flow is:

```text
SIGINT
  ↓
Parent stops generation
  ↓
Pipe write-end is closed
  ↓
Child detects end of input
  ↓
Child prints final statistics
  ↓
Parent waits for child
  ↓
Program terminates
```

Example:

```text
Parent: Stopping pulse generation...
Child: Final pulse count = 11
Child: Peak pulse rate = 1 pulse/sec
Parent: Child process finished.
```

---

# 📝 Logging

Processed pulse events are stored in:

```text
logs/pulse.log
```

Example:

```text
Child: Pulse received at 1000 ms | Total: 1
Child: Pulse received at 2000 ms | Total: 2
Child: Pulse received at 3000 ms | Total: 3
```

To view the log:

```bash
cat logs/pulse.log
```

For a fresh demonstration run:

```bash
rm -f logs/pulse.log
```

Then run the application again.

---

# 🧩 Linux Device Driver Component

The project includes:

```text
driver/powerpulse_driver.c
```

The driver demonstrates the structure of a Linux character-device driver
module.

It includes concepts such as:

* Linux kernel module initialization
* Linux kernel module cleanup
* `file_operations`
* Device `open`
* Device `release`
* Kernel logging using `printk`
* `module_init()`
* `module_exit()`

Conceptually:

```text
User Space Application
          |
          |
          ▼
   Linux Device Layer
          |
          ▼
 Character Device Driver
          |
          ▼
     Kernel Space
```

## Current Driver Status

The included driver is a **character-device driver skeleton**, not a fully
registered production driver.

It currently demonstrates the driver lifecycle and relevant architecture,
but does not yet implement:

* `register_chrdev()` / `cdev`
* Device-node creation
* Driver `read()` implementation
* Driver `write()` implementation
* Kernel-to-user-space pulse transfer

The current WSL2 environment does not provide the matching kernel build tree
required to compile and load the module.

Therefore, the **user-space PowerPulse application is the working executable
prototype**, while the driver source demonstrates the applicable Linux
device-driver concepts.

---

# 🏛️ Architecture Principles

The project follows separation of responsibilities.

```text
Pulse Generation
       ↓
Process Management
       ↓
IPC
       ↓
Pulse Processing
       ↓
Counting + Analytics
       ↓
Logging
```

Each responsibility is isolated into its own class/module.

This makes the system easier to:

* understand
* test
* maintain
* extend
* explain during evaluation

---

# 📊 Example Execution

A typical execution looks like:

```text
$ ./powerpulse

Parent: Generated pulse at 1000 ms
Processing pulse at 1000 ms
Child: Pulse received at 1000 ms | Total: 1

Parent: Generated pulse at 2000 ms
Processing pulse at 2000 ms
Analytics: Rate = 1 pulse/sec
Child: Pulse received at 2000 ms | Total: 2

Parent: Generated pulse at 3000 ms
Processing pulse at 3000 ms
Analytics: Rate = 1 pulse/sec
Child: Pulse received at 3000 ms | Total: 3
```

After pressing `Ctrl+C`:

```text
Parent: Stopping pulse generation...
Child: Final pulse count = 3
Child: Peak pulse rate = 1 pulse/sec
Parent: Child process finished.
```

---

# 📚 Documentation

Detailed project documentation is available in the `docs/` directory.

| Document              | Purpose                          |
| --------------------- | -------------------------------- |
| `PRD.md`              | Project requirements and scope   |
| `architecture.md`     | System architecture              |
| `class-diagram.md`    | C++ class relationships          |
| `sequence-diagram.md` | Runtime interaction sequence     |
| `state-machine.md`    | Application state transitions    |
| `driver.md`           | Linux driver concepts            |
| `execution.md`        | Build and execution instructions |
| `progress.md`         | Development stages and progress  |

---

# 🛠️ Development Stages

The project follows the development process specified for the training:

```text
Stage 1
Project Introduction
       ↓
Stage 2
Requirements & Development Plan
       ↓
Stage 3
System Design & Architecture
       ↓
Stage 4
Initial Implementation & Prototype
       ↓
Stage 5
Testing, Integration & Improvement
       ↓
Stage 6
Final Implementation & Presentation
```

The corresponding progress and documentation are maintained in:

```text
docs/progress.md
```

---

# ⚠️ Current Limitations

PowerPulse is a software prototype and therefore has several limitations:

1. Pulse generation is simulated rather than connected to physical
   smart-meter hardware.
2. Energy consumption is represented through pulse events rather than
   calibrated physical meter readings.
3. The current analytics focuses on pulse rate and peak pulse rate.
4. The driver is currently an architectural skeleton.
5. The current implementation does not use a database.
6. The project does not include a web or mobile frontend.
7. The application currently uses a single parent-child IPC pipeline.

These limitations are intentional to keep the project focused on Linux,
system programming, C++, and device-driver concepts.

---

# 🚀 Future Improvements

Future versions could include:

* Real smart-meter hardware integration
* Fully registered Linux character device
* Kernel `read()` / `write()` operations
* User-space and kernel-space pulse communication
* Configurable pulse-generation frequency
* Energy-consumption conversion based on meter calibration
* Historical data storage
* Additional energy analytics
* Multiple meter support
* Automated integration testing
* Performance benchmarking

---

# 🔐 Design Philosophy

PowerPulse is intentionally designed as a **systems-oriented project**.

Instead of adding unnecessary web technologies or external services, the
project focuses on understanding the underlying execution pipeline:

```text
Linux
  ↓
Processes
  ↓
IPC
  ↓
C++
  ↓
Pulse Processing
  ↓
Analytics
  ↓
File I/O
  ↓
Device Driver Concepts
```

This allows the project to demonstrate both **C++ software architecture**
and **Linux system-level programming** in a single application.

---

# 👨‍💻 Author

**PowerPulse — Smart Energy Meter Pulse Counter & Analytics Agent**

Developed as an individual C++ and Linux system-programming project.

---

# 📄 License

This project is developed for educational and academic purposes.
