# PowerPulse — Class Diagram

## 1. Overview

The PowerPulse application follows an object-oriented design in C++.
Each major responsibility is represented by a separate class.

## 2. Classes

### Pulse

**Responsibility:** Represents a single pulse event.

**Attributes:**

* `timestamp`

**Methods:**

* `Pulse(unsigned long timestamp)`
* `getTimestamp()`

---

### PulseSource

**Responsibility:** Defines the interface for generating pulse events.

**Type:** Abstract base class

**Methods:**

* `generatePulse()`

---

### SimulatedPulseSource

**Responsibility:** Generates simulated pulse events.

**Inheritance:**

* `SimulatedPulseSource` → `PulseSource`

**Attributes:**

* `currentTime`

**Methods:**

* `SimulatedPulseSource()`
* `generatePulse()`

---

### PulseProcessor

**Responsibility:** Processes a received pulse.

**Methods:**

* `processPulse(const Pulse& pulse)`

---

### PulseCounter

**Responsibility:** Maintains the total number of received pulses.

**Attributes:**

* `count`

**Methods:**

* `PulseCounter()`
* `addPulse(const Pulse& pulse)`
* `getCount()`

---

### AnalyticsAgent

**Responsibility:** Calculates pulse-rate information.

**Attributes:**

* `totalPulses`
* `previousTimestamp`
* `peakRate`

**Methods:**

* `AnalyticsAgent()`
* `analyze(unsigned long timestamp)`
* `getTotalPulses()`
* `getPeakRate()`

---

### Logger

**Responsibility:** Writes processed pulse information to the log file.

**Attributes:**

* `fileDescriptor`

**Methods:**

* `Logger(const std::string& filePath)`
* `~Logger()`
* `log(const std::string& message)`

---

### SignalHandler

**Responsibility:** Handles application termination signals.

**Attributes:**

* `running`

**Methods:**

* `setup()`
* `isRunning()`

## 3. Relationships

```text
                 ┌─────────────────────┐
                 │     PulseSource     │
                 │   <<abstract>>      │
                 └──────────┬──────────┘
                            │
                       inherits
                            │
                            ▼
                 ┌─────────────────────┐
                 │ SimulatedPulseSource│
                 └──────────┬──────────┘
                            │
                      generates
                            │
                            ▼
                 ┌─────────────────────┐
                 │        Pulse        │
                 └──────────┬──────────┘
                            │
             ┌──────────────┼──────────────┐
             │              │              │
             ▼              ▼              ▼
      ┌─────────────┐ ┌─────────────┐ ┌───────────────┐
      │PulseProcessor│ │PulseCounter │ │AnalyticsAgent │
      └─────────────┘ └─────────────┘ └───────────────┘
                                            │
                                            │
                                            ▼
                                      Rate Analysis


      ┌───────────────┐
      │    Logger     │
      └───────┬───────┘
              │
              ▼
        pulse.log


      ┌────────────────┐
      │ SignalHandler  │
      └───────┬────────┘
              │
              ▼
        SIGINT / SIGTERM
```

## 4. OOP Concepts Demonstrated

| Concept           | PowerPulse Implementation                       |
| ----------------- | ----------------------------------------------- |
| Encapsulation     | Private class attributes                        |
| Abstraction       | `PulseSource` abstract interface                |
| Inheritance       | `SimulatedPulseSource` inherits `PulseSource`   |
| Polymorphism      | `generatePulse()` uses `virtual` and `override` |
| Composition/Usage | Processing classes operate on `Pulse` objects   |
| Constructors      | Used to initialize class state                  |
| Destructors       | `Logger` closes its file descriptor             |

## 5. Main Design Principle

The project separates responsibilities into independent classes.

For example:

```text
Pulse generation
       ↓
Pulse representation
       ↓
Processing
       ↓
Counting
       ↓
Analytics
       ↓
Logging
```

This separation improves maintainability and makes individual components
easier to test.
