#include "time.hpp"
#include <ctime>

Time getCurrentTime(){
    Time t;
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    t.year = localTime->tm_year + 1900;
    t.month = localTime->tm_mon + 1;
    t.day = localTime->tm_mday;
    t.hour = localTime->tm_hour;
    t.minute = localTime->tm_min;
    t.second = localTime->tm_sec;
    return t;
}