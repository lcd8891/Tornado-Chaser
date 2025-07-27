#pragma once
#include <variant>
#include "../../types.hpp"
#include "../../vector.hpp"
#include <string>

struct Text{
    vector2<int> position;
    uint8 scale;
    std::string str;
    vector3<float> color;
    Text(vector2<int> _position, uint8 _scale, std::string _str, vector3<float> _color = {255,255,255});
};

using Elements = std::variant<
    Text
>;