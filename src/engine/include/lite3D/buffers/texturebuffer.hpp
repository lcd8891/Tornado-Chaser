#pragma once
#include <string>

class Texture;

namespace TextureBuffer{
    Texture* load_from_res(std::string _path,std::string _i);
    Texture* get(std::string _i);
    void delete_texture(std::string _i);
    void delete_all();
}