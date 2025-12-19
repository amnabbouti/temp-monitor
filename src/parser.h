#pragma once

#include <optional>
#include <string>

#include "types.h"

// Parse one line: "timestamp_ms,value"
// Strict rules:
// - nullopt on any garbage (missing comma, partial numbers, empty fields)
// - no exceptions, no allocations beyond the input string
std::optional<Sample> parse_sample_line(const std::string& line);
