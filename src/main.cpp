#include <iostream>   // std::cin, std::cout, std::cerr
#include <limits>     // std::numeric_limits (not strictly needed yet, but useful later)

/*
  temp-monitor (starter step)

  Goal of this step:
  - Build a tiny CLI program with deterministic behavior.
  - Read integer values from standard input (stdin).
  - Print "OK" if value <= threshold, otherwise print "WARNING".
  - Stop when input ends (EOF) or when input is invalid.
  - Return a non-zero exit code if input is invalid (useful for automation/CI).

  Why stdin?
  - In critical/embedded style software, we often separate:
      * pure logic (decisions) from
      * I/O (reading sensors, logs, files).
  - stdin is the simplest I/O we can use for now:
      * easy to test with piping:  echo "..." | program
      * easy to reproduce runs exactly (same input -> same output)
*/

int main() {
    /*
      WARNING_THRESHOLD:
      - A compile-time constant (constexpr) integer.
      - In real systems, thresholds might be in config or calibration data,
        but for a first step we hardcode it.
    */
    constexpr int WARNING_THRESHOLD = 70;

    /*
      value:
      - Will hold the last integer read from input.
      - Initialize to 0 for cleanliness (not strictly required).
    */
    int value = 0;

    /*
      Main input loop:

      "while (std::cin >> value)" means:
      - Try to read an integer from stdin into 'value'
      - If it succeeds, the expression is "true" and the loop runs.
      - If it fails, the expression is "false" and the loop stops.

      Reasons it can stop:
      1) EOF (end-of-file): user pressed Ctrl+D, or piped file ended.
      2) Invalid input: a non-integer token appeared (like "abc").

      This pattern is considered safe and idiomatic in C++ for input loops.
    */
    while (std::cin >> value) {
        /*
          Decision logic:

          We keep it extremely simple:
          - if value > threshold -> WARNING
          - else -> OK

          Note:
          - For critical software, being explicit is preferred over cleverness.
          - The output is deterministic and easy to validate.
        */
        if (value > WARNING_THRESHOLD) {
            std::cout << "WARNING: high value (" << value << ")\n";
        } else {
            std::cout << "OK: value = " << value << "\n";
        }
    }

    /*
      After the loop, we check WHY it stopped:

      - If we reached EOF, that's normal (no error).
      - If std::cin.fail() is true and it's NOT EOF, then input was invalid.

      This matters because:
      - In real systems, distinguishing "no more data" from "corrupt data"
        is critical for fault handling.
    */
    if (!std::cin.eof() && std::cin.fail()) {
        std::cerr << "ERROR: invalid input (expected integer values)\n";

        /*
          Return 1 indicates failure.
          - Scripts/CI tools can detect this.
          - It is a simple form of "error signaling".
        */
        return 1;
    }

    /*
      Return 0 indicates success.
      - Normal termination after processing all valid input.
    */
    return 0;
}

/*
  How to run (examples):

  1) Manual typing:
     ./build/temp-monitor
     then type:
       50
       80
       Ctrl+D (EOF)

  2) Pipe input:
     echo -e "50\n80\n60" | ./build/temp-monitor

  3) Invalid input:
     echo -e "50\nabc\n60" | ./build/temp-monitor
     (prints ERROR and exits with code 1)

  Check exit code:
     echo $?
*/

