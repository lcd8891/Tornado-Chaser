#include <string>
#include <lite3D/lite_utils.hpp>
#include <functional>

namespace{
    std::hash<std::string> hasher;
}

Identificator::Identificator(IdentifierGroup _group,std::string _key):group(_group),key(_key){}

namespace Identifier{
    uint64 of(Identificator _identificator){
        uint64 keyHash = hasher(_identificator.key);
        constexpr uint64 keyMask = (1ULL << 56) - 1;
        uint64 keyPart = keyHash & keyMask;
        uint64 groupPart = (uint64)(_identificator.group) & 0xFF; groupPart <<= 56;
        return keyPart | groupPart;
    }
}