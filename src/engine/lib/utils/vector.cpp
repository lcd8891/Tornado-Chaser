#include <lite3D/utils/vector.hpp>

glm::vec3 vectoGLM(vector3<float> _vec){
    return glm::vec3(_vec.x,_vec.y,_vec.z);
}
glm::ivec3 vectoGLM(vector3<int> _vec){
    return glm::ivec3(_vec.x,_vec.y,_vec.z);
}

vector3<float> GLMtovec(glm::vec3 _vec){
    return vector3<float>(_vec.x,_vec.y,_vec.z);
}
vector3<int> GLMtovec(glm::ivec3 _vec){
    return vector3<int>(_vec.x,_vec.y,_vec.z);
}