#include <lite3D/glutils/mesh.hpp>
#include <GL/glew.h>

Mesh::Mesh(const float* _buffer,uint64 _vertices,const int* _attr):vertices(_vertices){
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
void Mesh::reload(const float* _buffer,uint64 _vertices){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * _vertices, _buffer, GL_STATIC_DRAW);
	this->vertices = _vertices;
}
void Mesh::draw(Primitive _primitive){
    glBindVertexArray(vao);
    glDrawArrays((unsigned int)(_primitive),0,vertices);
    glBindVertexArray(0);
}
void Mesh::draw_part(Primitive _primitive,uint64 _vertices,uint64 _offset){
    glBindVertexArray(vao);
    glDrawArrays((unsigned int)(_primitive),_offset,_vertices);
    glBindVertexArray(0);
}


DynamicMesh::DynamicMesh(const float* _buffer,uint64 _vertices,const int* _attr):vertices(_vertices){
    vertex_size = 0;
    for(int i = 0;_attr[i];i++){
        vertex_size += _attr[i];
    }
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);

    glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_size*_vertices, _buffer,GL_DYNAMIC_DRAW);

    int offset = 0;
    for(int i = 0;_attr[i];i++){
        int size = _attr[i];
	    glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size*sizeof(float), (GLvoid*)(offset*sizeof(float)));
	    glEnableVertexAttribArray(i);
        offset += _attr[i];
    }

	glBindVertexArray(0);
}
DynamicMesh::~DynamicMesh(){
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
}
void DynamicMesh::reload(const float* _buffer,uint64 _vertices){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * _vertices, _buffer, GL_DYNAMIC_DRAW);
	this->vertices = _vertices;
}
void DynamicMesh::reload_part(const float* _buffer,uint64 _vertices,uint64 _offset){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * _offset, _vertices * vertex_size * sizeof(float), _buffer);
	this->vertices = _vertices;
}
void DynamicMesh::draw(Primitive _primitive){
    glBindVertexArray(vao);
    glDrawArrays((unsigned int)(_primitive),0,vertices);
    glBindVertexArray(0);
}
void DynamicMesh::draw_part(Primitive _primitive,uint64 _vertices,uint64 _offset){
    glBindVertexArray(vao);
    glDrawArrays((unsigned int)(_primitive),_offset,_vertices);
    glBindVertexArray(0);
}