#pragma once
#include <string>
#include <lite3D/lite_utils.hpp>

enum class IdentifierGroup{
    Shader,
    Texture,
    Sound,
    Font,
    Music
};

struct Identificator{
    IdentifierGroup group;
    std::string key;
    Identificator(IdentifierGroup _group,std::string _key);
};

namespace Identifier{
    uint64 of(Identificator _identificator);
}