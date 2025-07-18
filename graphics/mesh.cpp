#include "mesh.hpp"
#include <GL/glew.h>

Mesh::Mesh(const float* _buffer,size _vertices,const int* _attr):vertices(_vertices){
    vertex_size = 0;
    for(int i = 0;_attr[i];i++){
        vertex_size += _attr[i];
    }
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);

    glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_size*_vertices, _buffer,GL_STATIC_DRAW);

    int offset = 0;
    for(int i = 0;_attr[i];i++){
        int size = _attr[i];
	    glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size*sizeof(float), (GLvoid*)(offset*sizeof(float)));
	    glEnableVertexAttribArray(i);
        offset += _attr[i];
    }

	glBindVertexArray(0);
}
Mesh::~Mesh(){
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
}
void Mesh::reload(const float* _buffer,size _vertices){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * _vertices, _buffer, GL_STATIC_DRAW);
	this->vertices = _vertices;
}
void Mesh::draw(unsigned int _primitive){
    glBindVertexArray(vao);
    glDrawArrays(_primitive,0,vertices);
    glBindVertexArray(0);
}