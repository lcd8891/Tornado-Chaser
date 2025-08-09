#pragma once
#include <string>
#include "types.hpp"

namespace Logger{
    void initialize();
    void open_file();
    
    void info(std::string str);
    void waning(std::string str);
    void error(std::string str);
    void terminate(const EXIT_INFO &_ei);
}