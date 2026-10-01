cmake_minimum_required(VERSION 3.16)

project(PowerPulse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Main application
add_executable(powerpulse
    src/main.cpp
    src/core/Pulse.cpp
    src/core/PulseCounter.cpp
    src/core/PulseProcessor.cpp
    src/core/AnalyticsAgent.cpp
    src/sources/SimulatedPulseSource.cpp
    src/system/Logger.cpp
    src/system/SignalHandler.cpp
)

# Unit test
add_executable(test_pulse
    tests/test_pulse.cpp
    src/core/Pulse.cpp
    src/core/PulseCounter.cpp
    src/core/AnalyticsAgent.cpp
)