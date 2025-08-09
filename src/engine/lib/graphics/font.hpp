#pragma once
#include <string>

class Texture;

namespace FontLoader{
    void initialize();
    Texture* updateLocale(std::string _locale);
    void cleanup();
}