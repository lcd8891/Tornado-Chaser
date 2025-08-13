#pragma once
#include <glm/glm.hpp>

template<typename T>
struct vector2{
    T x;
    T y;
    vector2(T _x,T _y):x(_x),y(_y){}
    vector2(){}
};

template<typename T>
struct vector3{
    T x;
    T y;
    T z;
    vector3(T _x,T _y,T _z):x(_x),y(_y),z(_z){}
    vector3(){}
};

glm::vec3 vectoGLM(vector3<float> _vec);
glm::ivec3 vectoGLM(vector3<int> _vec);

vector3<float> GLMtovec(glm::vec3 _vec);
vector3<int> GLMtovec(glm::ivec3 _vec);