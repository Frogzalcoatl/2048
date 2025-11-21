#include "2048/game/stringToInt.hpp"
#include <charconv>

uint64_t stringToUInt64(const std::string& str) {
    uint64_t value;
    auto result = std::from_chars(str.data(), str.data() + str.size(), value);
    if (result.ec != std::errc()) {
        return 0;
    }
    return value;
}