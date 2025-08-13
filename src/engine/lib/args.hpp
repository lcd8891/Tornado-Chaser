#pragma once
#include <string>

namespace Args{
    extern bool cmd;
    extern std::string gamecomp;
    void parse(int argc, char** argv);
}