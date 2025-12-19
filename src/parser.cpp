#include "parser.h"

#include <charconv>   // from_chars: fast, no locale, no exceptions
#include <system_error>

namespace {

// Minimal trimming. Accept spaces, but keep rules strict.
std::string_view trim(std::string_view sv) {
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.front())))
        sv.remove_prefix(1);
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.back())))
        sv.remove_suffix(1);
    return sv;
}

// from_chars: no allocations, no exceptions, no locale surprises.
bool parse_i64(std::string_view sv, std::int64_t& out) {
    sv = trim(sv);
    if (sv.empty()) return false;

    const char* b = sv.data();
    const char* e = sv.data() + sv.size();
    auto r = std::from_chars(b, e, out);

    // Require full consumption. "123abc" is garbage.
    return r.ec == std::errc{} && r.ptr == e;
}

bool parse_int(std::string_view sv, int& out) {
    sv = trim(sv);
    if (sv.empty()) return false;

    const char* b = sv.data();
    const char* e = sv.data() + sv.size();
    auto r = std::from_chars(b, e, out);

    return r.ec == std::errc{} && r.ptr == e;
}

} // namespace

std::optional<Sample> parse_sample_line(const std::string& line) {
    // Empty line is not data.
    if (line.empty()) return std::nullopt;

    std::string_view sv(line);
    const std::size_t comma = sv.find(',');
    if (comma == std::string_view::npos) return std::nullopt;

    const std::string_view left = sv.substr(0, comma);
    const std::string_view right = sv.substr(comma + 1);

    std::int64_t ts = 0;
    int v = 0;

    if (!parse_i64(left, ts)) return std::nullopt;
    if (!parse_int(right, v)) return std::nullopt;

    return Sample{ts, v};
}
