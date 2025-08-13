#include <lite3D/graphics/camera.hpp>
#include <lite3D/lite_window.hpp>
#include <glm/ext.hpp>

Camera::Camera(vector3<float> _position,float _fov):position(vectoGLM(_position)),fov(glm::radians(_fov)),zoom(1),rotation(1){
    updateVectors();
};

void Camera::updateVectors(){
	front = glm::vec3(rotation * glm::vec4(0,0,-1,1));
	right = glm::vec3(rotation * glm::vec4(1,0,0,1));
	up = glm::vec3(rotation * glm::vec4(0,1,0,1));
	dir = glm::vec3(rotation * glm::vec4(0,0,-1,1));
	dir.y = 0;
	float len = length(dir);
	if (len > 0.0f){
		dir.x /= len;
		dir.z /= len;
	}
}
void Camera::rotate(vector3<float> _rotate){
	rotation = glm::rotate(rotation, _rotate.z, glm::vec3(0,0,1));
	rotation = glm::rotate(rotation, _rotate.y, glm::vec3(0,1,0));
	rotation = glm::rotate(rotation, _rotate.x, glm::vec3(1,0,0));

	updateVectors();
}
void Camera::setFOV(float fov){
	fov = glm::radians(fov);
}
glm::mat4 Camera::getView(){
	return glm::lookAt(position, position+front, up);
}
glm::mat4 Camera::getProjection(){
	float aspect = (float)Window::size.x / (float)Window::size.y;
	return glm::perspective(fov, aspect, 0.1f, 1500.0f);
}