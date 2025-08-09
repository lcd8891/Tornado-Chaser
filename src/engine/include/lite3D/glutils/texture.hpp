#pragma once
#include <string>
#include <lite3D/lite_utils.hpp>

class Texture{
    private:
    unsigned int ID;
    public:
    Texture(unsigned int _ID);
    Texture(void *pixdata, vector2<uint32> size,int colormode = 0x1908,bool linear = false);
    ~Texture();

    void use();
};

Texture* loadFromFile(std::string _str);
Texture* loadFromMemory(void *_data,size_t _size);