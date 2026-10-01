# PowerPulse Linux Device Driver

## Overview

PowerPulse includes a Linux kernel module that demonstrates the
Linux character-device driver architecture for a smart-meter pulse
monitoring system.

The driver is implemented in:

    driver/powerpulse_driver.c

## Driver Responsibilities

The driver provides the kernel-side foundation for the PowerPulse
pulse-monitoring system.

It demonstrates:

- Linux kernel module initialization
- Linux kernel module cleanup
- Character-device driver structure
- `open()` callback
- `release()` callback
- `file_operations`
- Kernel logging using `printk()`

## Driver Lifecycle

When the module is loaded:

    PowerPulse: driver loaded
    PowerPulse: character device ready

When the device is opened:

    PowerPulse: device opened

When the device is closed:

    PowerPulse: device closed

When the module is unloaded:

    PowerPulse: driver unloaded

## Architecture

    Smart Meter Pulse
            |
            v
    Linux Device Driver
    powerpulse_driver.c
            |
            v
    User-Space C++ Application
            |
            +--> PulseCounter
            |
            +--> PulseProcessor
            |
            +--> AnalyticsAgent
            |
            +--> Logger

## Build

The driver uses the Linux kernel module build system:

    make

The Makefile invokes:

    /lib/modules/$(uname -r)/build

to obtain the kernel build environment.

## Current Environment Limitation

The development environment uses WSL2.

The running WSL kernel is:

    6.18.33.2-microsoft-standard-WSL2

The matching kernel build directory is not currently available:

    /lib/modules/6.18.33.2-microsoft-standard-WSL2/build

Therefore, the kernel module has not been compiled or loaded in the
current development environment.

The driver source and Makefile are included as part of the project
architecture and can be compiled in a Linux environment with matching
kernel build sources.

## Important

The current driver is a character-device driver skeleton intended to
demonstrate Linux device-driver concepts. The actual pulse generation
and analytics currently run in user space through the simulated pulse
source.