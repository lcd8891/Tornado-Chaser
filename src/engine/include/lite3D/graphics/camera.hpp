#pragma once

#include <glm/glm.hpp>
#include "../lite_utils.hpp"

class Camera{
    private:
    void updateVectors();
    public:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 dir;
    glm::vec3 right;

    float fov;
    float zoom;
    glm::vec3 position;
    glm::mat4 rotation;

    Camera(vector3<float> _position,float _fov = 75);
    void rotate(vector3<float> _rotate);
    void setFOV(float fov);
    glm::mat4 getView();
    glm::mat4 getProjection();
};