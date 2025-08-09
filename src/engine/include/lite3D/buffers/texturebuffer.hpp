#pragma once
#include <string>

class Texture;
struct Identificator;

namespace TextureBuffer{
    Texture* load_from_res(std::string _path,Identificator _i);
    Texture* get(Identificator _i);
    void delete_texture(Identificator _i);
    void delete_all();
}