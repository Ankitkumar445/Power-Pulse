# PowerPulse — State Machine Diagram

## 1. Overview

The state machine represents the major execution states of the PowerPulse
application from startup to shutdown.

## 2. Application States

```text
                         ┌───────────────┐
                         │   STARTING    │
                         └───────┬───────┘
                                 │
                                 │ initialize
                                 ▼
                         ┌───────────────┐
                         │   CREATING    │
                         │    PIPE       │
                         └───────┬───────┘
                                 │
                                 │ fork()
                                 ▼
                         ┌───────────────┐
                         │    RUNNING    │
                         └───────┬───────┘
                                 │
                    ┌────────────┴────────────┐
                    │                         │
              generate pulse             SIGINT/SIGTERM
                    │                         │
                    ▼                         ▼
             ┌───────────────┐       ┌────────────────┐
             │ PULSE GENERATED│       │   STOPPING     │
             └───────┬───────┘       └───────┬────────┘
                     │                       │
                     │ write()               │ close pipe
                     ▼                       ▼
             ┌───────────────┐       ┌────────────────┐
             │ PULSE SENT    │       │ CHILD FINISHING│
             └───────┬───────┘       └───────┬────────┘
                     │                       │
                     │ pipe                  │ final stats
                     ▼                       ▼
             ┌───────────────┐       ┌────────────────┐
             │ PULSE RECEIVED│       │   TERMINATED   │
             └───────┬───────┘       └────────────────┘
                     │
                     ▼
             ┌───────────────┐
             │   PROCESSING  │
             └───────┬───────┘
                     │
          ┌──────────┼──────────┐
          │          │          │
          ▼          ▼          ▼
       Counter    Analytics    Logger
          │          │          │
          └──────────┼──────────┘
                     │
                     ▼
             ┌───────────────┐
             │ WAIT / NEXT   │
             │    PULSE      │
             └───────┬───────┘
                     │
                     │ after 1 second
                     │
                     └──────────────► RUNNING
```

## 3. State Descriptions

| State             | Description                                                  |
| ----------------- | ------------------------------------------------------------ |
| STARTING          | Application begins execution                                 |
| CREATING PIPE     | Linux IPC pipe is created                                    |
| RUNNING           | Parent and child processes are active                        |
| PULSE GENERATED   | Simulated pulse is created                                   |
| PULSE SENT        | Parent writes timestamp to the pipe                          |
| PULSE RECEIVED    | Child reads timestamp from the pipe                          |
| PROCESSING        | Pulse is processed, counted, analyzed, and logged            |
| WAIT / NEXT PULSE | Parent waits before generating another pulse                 |
| STOPPING          | Parent receives a termination signal                         |
| CHILD FINISHING   | Child completes remaining work and displays final statistics |
| TERMINATED        | Application exits                                            |

## 4. State Transitions

### Startup

```text
STARTING → CREATING PIPE → RUNNING
```

### Normal Operation

```text
RUNNING
   ↓
PULSE GENERATED
   ↓
PULSE SENT
   ↓
PULSE RECEIVED
   ↓
PROCESSING
   ↓
WAIT / NEXT PULSE
   ↓
RUNNING
```

The cycle continues while the application is running.

### Shutdown

```text
RUNNING
   ↓
SIGINT / SIGTERM
   ↓
STOPPING
   ↓
close(pipe)
   ↓
CHILD FINISHING
   ↓
TERMINATED
```

## 5. Processing State

During the `PROCESSING` state, the child performs the following operations:

```text
                 PROCESSING
                      |
        ┌─────────────┼─────────────┐
        ▼             ▼             ▼
   PulseCounter  AnalyticsAgent   Logger
        |             |             |
        ▼             ▼             ▼
    Count + 1     Rate/Peak     pulse.log
```

## 6. Error Considerations

The application checks important Linux operations such as:

* `pipe()`
* `fork()`
* `open()`
* `read()`
* `write()`

If process or pipe creation fails, the application reports an error and
terminates rather than continuing with an invalid IPC state.

## 7. Design Purpose

The state model separates the normal pulse-processing lifecycle from the
shutdown lifecycle.

This makes the system behavior easier to understand, test, and explain
during project evaluation.
