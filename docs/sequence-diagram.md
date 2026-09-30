# PowerPulse — Sequence Diagram

## 1. Overview

The sequence diagram shows how a pulse moves through the PowerPulse system
during normal execution.

The application uses two Linux processes:

* **Parent Process** — generates simulated pulses.
* **Child Process** — receives and processes pulse data.

The processes communicate using a Linux pipe.

## 2. Runtime Sequence

```text
SimulatedPulseSource    Parent Process       Linux Pipe       Child Process
       |                     |                   |                  |
       | generatePulse()     |                   |                  |
       |<--------------------|                   |                  |
       |                     |                   |                  |
       |------ Pulse -------->|                   |                  |
       |                     |                   |                  |
       |                     | write(timestamp) |                  |
       |                     |------------------>|                  |
       |                     |                   |                  |
       |                     |                   | read(timestamp) |
       |                     |                   |----------------->|
       |                     |                   |                  |
       |                     |                   |                  |
       |                     |                   |       Pulse      |
       |                     |                   |       object     |
       |                     |                   |        created   |
       |                     |                   |                  |
       |                     |                   |                  |
       |                     |                   |   processPulse() |
       |                     |                   |<-----------------|
       |                     |                   |                  |
       |                     |                   |   addPulse()     |
       |                     |                   |<-----------------|
       |                     |                   |                  |
       |                     |                   |   analyze()      |
       |                     |                   |<-----------------|
       |                     |                   |                  |
       |                     |                   |      log()       |
       |                     |                   |<-----------------|
       |                     |                   |                  |
       |                     |                   |                  |
       |                     |                   |      pulse.log   |
       |                     |                   |          |       |
       |                     |                   |          ▼       |
       |                     |                   |      Log entry   |
       |                     |                   |                  |
       |                     |                   |                  |
       |                     |   wait 1 second   |                  |
       |                     |-------------------|----------------->|
       |                     |                   |                  |
       |                     |      repeat       |                  |
       |                     |                   |                  |
```

## 3. Process Creation

At application startup:

```text
                     main()
                       |
                       ▼
                  pipe(pipefd)
                       |
                       ▼
                    fork()
                   /      \
                  /        \
                 ▼          ▼
          Parent Process   Child Process
```

The parent and child use different ends of the pipe:

```text
Parent Process                     Child Process
      |                                  |
      | pipefd[1]                        | pipefd[0]
      |                                  |
      └────────── Linux Pipe ────────────┘
                 IPC channel
```

## 4. Pulse Processing Sequence

For each generated pulse:

1. `SimulatedPulseSource` generates a pulse.
2. The parent extracts the timestamp.
3. The parent writes the timestamp to the pipe.
4. The child reads the timestamp.
5. The child creates a `Pulse` object.
6. `PulseProcessor` processes the pulse.
7. `PulseCounter` increments the pulse count.
8. `AnalyticsAgent` calculates the pulse rate.
9. `Logger` writes the event to `pulse.log`.
10. The parent waits before generating the next pulse.

## 5. Shutdown Sequence

When the user presses `Ctrl+C`:

```text
User
 |
 | Ctrl+C
 ▼
SIGINT
 |
 ▼
Parent Process
 |
 | stop generation
 ▼
close(pipefd[1])
 |
 ▼
Child receives EOF
 |
 ▼
Child finishes processing
 |
 ▼
Child prints final statistics
 |
 ▼
Parent calls wait()
 |
 ▼
Application terminates
```

## 6. Important Linux Concepts

The sequence demonstrates:

* `fork()` — process creation
* `pipe()` — IPC channel creation
* `write()` — parent-to-child communication
* `read()` — child receiving data
* `close()` — resource cleanup
* `wait()` — parent waits for child
* `SIGINT` — graceful termination
* File descriptors — Linux resource handles

## 7. Data Flow

```text
Pulse Timestamp
      |
      ▼
Parent Process
      |
      | write()
      ▼
Linux Pipe
      |
      | read()
      ▼
Child Process
      |
      ▼
Pulse Object
      |
      ├──────────► PulseProcessor
      |
      ├──────────► PulseCounter
      |
      ├──────────► AnalyticsAgent
      |
      └──────────► Logger
                         |
                         ▼
                    pulse.log
```
