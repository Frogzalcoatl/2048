#include "2048/game/stringToInt.hpp"
#include <charconv>
using namespace std;

uint64_t stringToUInt64(const string& str) {
    uint64_t value;
    auto result = from_chars(str.data(), str.data() + str.size(), value);
    if (result.ec != errc()) {
        return 0;
    }
    return value;
}