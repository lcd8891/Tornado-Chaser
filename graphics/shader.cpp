#include "shader.hpp"
#include <GL/glew.h>
#include "../types.hpp"
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

std::string loadStringFromFile(std::string Path){
    std::ifstream file(Path);
    if(!file.is_open()){throw EXIT_INFO("Shader file not found: "+Path,3);}
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(unsigned int _ID):ID(_ID){}
Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::uniformMatrix(std::string name,glm::mat4 _mat){
    GLuint location = glGetUniformLocation(ID,name.c_str());
    glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(_mat));
}
void Shader::uniformInt(std::string name,int _int){
    GLuint location = glGetUniformLocation(ID,name.c_str());
    glUniform1i(location,_int);
}
void Shader::uniformFloat(std::string name,float _float){
    GLuint location = glGetUniformLocation(ID,name.c_str());
    glUniform1f(location,_float);
}
void Shader::uniform2Float(std::string name,float _x,float _y){
    GLuint location = glGetUniformLocation(ID,name.c_str());
    glUniform2f(location,_x,_y);
}
void Shader::uniform3Float(std::string name,float _x,float _y,float _z){
    GLuint location = glGetUniformLocation(ID,name.c_str());
    glUniform3f(location,_x,_y,_z);
}

Shader *initShaderFromFile(std::string vertPath,std::string fragPath,std::string geomPath){
    std::string vertstr = loadStringFromFile(vertPath);
    std::string fragstr = loadStringFromFile(fragPath);
    const GLchar* vertCode = vertstr.c_str();
    const GLchar* fragCode = fragstr.c_str();

    GLuint vertex,fragment,geometry;
    GLint success;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertCode,nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        std::string infoLog;
        infoLog.resize(512);
        glGetShaderInfoLog(vertex,512,nullptr,&infoLog[0]);
        throw EXIT_INFO(infoLog+"\nvertex shader compilation error!",4);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragCode,nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        std::string infoLog;
        infoLog.resize(512);
        glGetShaderInfoLog(fragment,512,nullptr,&infoLog[0]);
        glDeleteShader(vertex);
        throw EXIT_INFO(infoLog+"\nfragment shader compilation error!",5);
    }

    GLuint ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);

    if(geomPath!=""){
        std::string geomstr = loadStringFromFile(geomPath);
        const GLchar* geomCode = geomstr.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry,1,&geomCode,nullptr);
        glCompileShader(geometry);
        glGetShaderiv(geometry,GL_COMPILE_STATUS,&success);
        if(!success){
            std::string infoLog;
            infoLog.resize(512);
            glGetShaderInfoLog(geometry,512,nullptr,&infoLog[0]);
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            throw EXIT_INFO(infoLog+"\ngeometry shader compilation error!",6);
        }
        glAttachShader(ID,geometry);
    }
    glLinkProgram(ID);
    
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        std::string infoLog;
        glGetProgramInfoLog(ID,512,nullptr,&infoLog[0]);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(glIsShader(geometry))glDeleteShader(geometry);
        glDeleteProgram(ID);
        throw EXIT_INFO("shader linking error",7);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(glIsShader(geometry))glDeleteShader(geometry);

    return new Shader(ID);
}

Shader *initShaderFromString(std::string vertPath,std::string fragPath,std::string geomPath){
    const GLchar* vertCode = vertPath.c_str();
    const GLchar* fragCode = fragPath.c_str();

    GLuint vertex,fragment,geometry;
    GLint success;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertCode,nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        std::string infoLog;
        infoLog.resize(512);
        glGetShaderInfoLog(vertex,512,nullptr,&infoLog[0]);
        throw EXIT_INFO(infoLog+"\nvertex shader compilation error!",4);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragCode,nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        std::string infoLog;
        infoLog.resize(512);
        glGetShaderInfoLog(fragment,512,nullptr,&infoLog[0]);
        glDeleteShader(vertex);
        throw EXIT_INFO(infoLog+"\nfragment shader compilation error!",5);
    }

    GLuint ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);

    if(geomPath!=""){
        const GLchar* geomCode = geomPath.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry,1,&geomCode,nullptr);
        glCompileShader(geometry);
        glGetShaderiv(geometry,GL_COMPILE_STATUS,&success);
        if(!success){
            std::string infoLog;
            infoLog.resize(512);
            glGetShaderInfoLog(geometry,512,nullptr,&infoLog[0]);
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            throw EXIT_INFO(infoLog+"\ngeometry shader compilation error!",6);
        }
        glAttachShader(ID,geometry);
    }
    
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        std::string infoLog;
        glGetProgramInfoLog(ID,512,nullptr,&infoLog[0]);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(glIsShader(geometry))glDeleteShader(geometry);
        glDeleteProgram(ID);
        throw EXIT_INFO("shader linking error",7);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(glIsShader(geometry))glDeleteShader(geometry);

    return new Shader(ID);
}