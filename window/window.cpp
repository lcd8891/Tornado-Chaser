#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace{
    const unsigned short default_size[2];
}

namespace Window{
    GLFWwindow *window;
    void initialize(std::string name, unsigned short size[2]){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE,true);

        window = glfwCreateWindow(size[0],size[1],name.c_str(),nullptr,nullptr);
        if(!window){
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glewExperimental = true;
        if(glewInit()!=GLEW_OK){
            glfwTerminate();
        }
        
        
    }
}