#pragma once
#include <string>

using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using uint32 = unsigned int;
using int64 = long;
using uint64 = unsigned long;

struct EXIT_INFO{
    std::string info;
    uint32 code;
    EXIT_INFO(std::string _info, uint32 _code):info(_info),code(_code){}
};