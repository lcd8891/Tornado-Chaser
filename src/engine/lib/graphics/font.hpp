#pragma once
#include <string>

namespace FontLoader{
    void initialize();
    void updateLocale(std::string _locale);
    void cleanup();
}