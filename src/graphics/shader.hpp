#pragma once
#include <string>
#include <glm/matrix.hpp>

class Shader{
    public:
    unsigned int ID;
    ~Shader();
    Shader(unsigned int _ID);

    void use();

    void uniformMatrix(std::string name,glm::mat4 _mat);
    void uniformInt(std::string name,int _int);
    void uniformFloat(std::string name,float _float);
    void uniform2Float(std::string name,float _x,float _y);
    void uniform3Float(std::string name,float _x,float _y,float _z);
};

Shader *initShaderFromFile(std::string vertPath,std::string fragPath,std::string geomPath = "");
Shader *initShaderFromString(std::string vertPath,std::string fragPath,std::string geomPath = "");