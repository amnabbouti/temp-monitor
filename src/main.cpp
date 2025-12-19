#include <iostream>  // stdin/stdout/stderr

int main() {
    // Hardcoded threshold is fine for a starter.
    // Real code would make this configurable, but don't overdesign yet.
    constexpr int WARNING_THRESHOLD = 70;

    int value = 0;

    // Read ints until EOF or garbage input.
    // This keeps behavior deterministic and easy to test with pipes.
    while (std::cin >> value) {
        // Keep the rule boring and explicit.
        if (value > WARNING_THRESHOLD) {
            std::cout << "WARNING: high value (" << value << ")\n";
        } else {
            std::cout << "OK: value = " << value << "\n";
        }
    }

    // If we didn't hit EOF, input was malformed (e.g. "abc").
    // Fail with non-zero so scripts/CI can catch it.
    if (!std::cin.eof() && std::cin.fail()) {
        std::cerr << "ERROR: invalid input (expected integer values)\n";
        return 1;
    }

    return 0;
}
