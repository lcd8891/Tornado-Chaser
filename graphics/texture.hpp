#pragma once
#include <string>

class Texture{
    unsigned int ID;
    public:
    Texture(unsigned int _ID);
    ~Texture();

    void use();
};

Texture* loadFromFile(std::string _str);
Texture* loadFromMemory(void *_data,size_t _size);