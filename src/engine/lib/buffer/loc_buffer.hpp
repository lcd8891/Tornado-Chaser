#pragma once
#include <string>

class Texture;
class Shader;

namespace TextureBuffer{
    void setTexture(std::string _i, Texture* _t);
}
namespace ShaderBuffer{
    void setShader(std::string _i, Shader* _s);
}