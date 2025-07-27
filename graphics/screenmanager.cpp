#include "screenmanager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../window/window.hpp"
#include "../types.hpp"
#include "../vector.hpp"
#include "shader.hpp"

namespace Screenmanager{
    glm::mat4 screenView;
    void recalculate_screenview(){
        vector2<int> size = Window::size;
        glm::mat4 mat(1.f);
        mat = glm::translate(mat,glm::vec3(-1.f,1.f,0.f));
        mat = glm::scale(mat,glm::vec3(2.f / size.x,-2.f / size.y,1.f));
        screenView = mat;
    }
}