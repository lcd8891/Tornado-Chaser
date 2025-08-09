#pragma once

using size = unsigned long long; 

class Mesh{
    private:
    unsigned int vbo;
    unsigned int vao;
    size vertices;
    size vertex_size;
    public:
    Mesh(const float* _buffer,size _vertices,const int* _attr);
    ~Mesh();
    void reload(const float* _buffer,size _vertices);
    void draw(unsigned int _primitive);
    void draw(unsigned int _primitive,size _vertices,size offset = 0);
};