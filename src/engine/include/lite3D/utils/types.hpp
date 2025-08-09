#pragma once
#include <string>
#include "vector.hpp"

using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;

struct EXIT_INFO{
    std::string info;
    EXIT_INFO(std::string _info):info(_info){}
};