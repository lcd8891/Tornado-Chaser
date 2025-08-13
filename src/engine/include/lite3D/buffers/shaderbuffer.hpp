#pragma once
#include <string>

class Shader;

namespace ShaderBuffer{
    Shader* load_from_res(std::string _path,std::string _i);
    Shader* get(std::string _i);
    void delete_shader(std::string _i);
    void delete_all();
}