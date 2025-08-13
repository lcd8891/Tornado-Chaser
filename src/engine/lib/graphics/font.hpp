#pragma once
#include <string>
#include <map>
#include <lite3D/lite_utils.hpp>

#define CHAR_SIZE 64

struct CharMeta{
    vector2<float> tex_position; // Position in glyph_atlas texture
    vector2<float> tex_size;     // Size in glyph_atlas texture
    vector2<unsigned int> size;           // Size of glyph
    vector2<int> bearing;        // Bearing character from top left
    float advance;               // Advance of character
};

namespace FontLoader{
    extern std::map<int,CharMeta> charMap;
    void initialize();
    void updateLocale(std::string _locale);
    void cleanup();
}