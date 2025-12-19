#pragma once

#include <cstdint>
#include <string_view>

// Dumb data types (boring)
struct Sample {
	std::int64_t timestamp_ms{};
	int value{};
};

enum class MonitorState {
	OK,
	WARNING,
	ALARM,
	SENSOR_FAIL
};

inline std::string_view to_string(MonitorState s) {
	switch (s) {
		case MonitorState::OK: return "OK";
		case MonitorState::WARNING: return "WARNING";
		case MonitorState::ALARM: return "ALARM";
		case MonitorState::SENSOR_FAIL: return "SENSOR_FAIL";
	}
	return "UNKNOWN";

}