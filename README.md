# temp-monitor

A small C++ console program that reads temperature values from standard input
and emits a simple status (`OK` / `WARNING`) based on a fixed threshold.

This project is intentionally minimal and focused on:
- deterministic behavior
- explicit input validation
- clear control flow
- build-from-terminal workflow (CMake)

It is meant as a learning and portfolio project oriented toward
**systems / safety-critical style software**, not UI or web development.

---

## Behavior

- Reads integer values from **stdin**
- For each value:
  - `OK` if value ≤ 70
  - `WARNING` if value > 70
- Stops on end-of-file (EOF)
- Exits with error code `1` if input is invalid (non-integer)

---

## Build

Requirements:
- C++ compiler (GCC or Clang)
- CMake
- Ninja (recommended)

```bash
cmake -S . -B build -G Ninja
cmake --build build

