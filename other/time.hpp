#pragma once
#include "../types.hpp"

struct Time{
    uint16 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
    uint8 second;
};

Time getCurrentTime();