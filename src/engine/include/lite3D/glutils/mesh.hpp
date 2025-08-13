#pragma once
using size = unsigned long long; 

enum class Primitive{
    Points = 0x0,
    Lines = 0x1,
    Lines_adjacency = 0xa,
    Triangles = 0x4,
    Triangle_strip = 0x5
};

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
    void draw(Primitive _primitive);
    void draw(Primitive _primitive,size _vertices,size offset = 0);
};