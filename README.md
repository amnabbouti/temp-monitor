# temp-monitor

Temperature monitoring tool that reads CSV samples and tracks state transitions.

## What it does

Parses timestamped temperature readings from stdin in CSV format:

```
1234567890,65
1234567891,72
1234567892,95
```

Tracks monitor state based on temperature thresholds:

- **OK**: normal operating range
- **WARNING**: elevated temperature
- **ALARM**: critical temperature
- **SENSOR_FAIL**: invalid/missing data

Input validation is strict - malformed lines are rejected, no exceptions thrown, minimal allocations.

## Build

Requirements:

- C++20 compiler (GCC/Clang)
- CMake 3.20+
- Ninja (optional but recommended)

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/temp-monitor

```
