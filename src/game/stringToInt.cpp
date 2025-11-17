#include "2048/game/stringToInt.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

uint64_t stringToUInt64(string str) {
    uint64_t value;
    try {
        value = stoull(str);
    } catch (const invalid_argument&) {
        cerr << "No conversion could be performed" << endl;
        return 0;
    } catch (const out_of_range&) {
        cerr << "Converted value falls out of range of uint64_t" << endl;
        return 0;
    }
    return value;
}