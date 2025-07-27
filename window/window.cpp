#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "window.hpp"
#include "../vector.hpp"
#include "../types.hpp"
#include "../graphics/screenmanager.hpp"

namespace Window{
    GLFWwindow *window;
    vector2<int> size;
    bool mouse_locked = false;
    bool fullscreen = false;
    bool focus = true;
    void initialize(std::string _name, vector2<int> _size){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE,true);
        size=_size;
        window = glfwCreateWindow(_size.x,_size.y,_name.c_str(),nullptr,nullptr);
        if(!window){
            glfwTerminate();
            throw EXIT_INFO("Couldn't create new window!",1);
        }
        glfwMakeContextCurrent(window);
        glewExperimental = true;
        if(glewInit()!=GLEW_OK){
            glfwTerminate();
            throw EXIT_INFO("Couldn't initialize OpenGL!",2);
        }
        glViewport(0,0,size.x,size.y);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        glDepthFunc(GL_LESS);

        glfwSetWindowSizeLimits(window,800,600,-1,-1);
        Screenmanager::recalculate_screenview();
    }

    void close(){
        glfwSetWindowShouldClose(window,true);
    }
    bool isClose(){
        return glfwWindowShouldClose(window);
    }
    void display(){
        glfwSwapBuffers(window);
    }
    void lockMouse(bool locked){
        mouse_locked=locked;
        glfwSetInputMode(window,GLFW_CURSOR,locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
    void terminate(){
        glfwTerminate();
    }
    void setMouseType(int type){
        glfwSetCursor(window,glfwCreateStandardCursor(type));
    }
    void setFullscreen(bool _fullscreen){
        fullscreen = _fullscreen;
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        if(fullscreen){
            glfwSetWindowMonitor(window,monitor,0,0,mode->width,mode->height,mode->refreshRate);
            size.x=mode->width;size.y=mode->height;
        }else{
            glfwSetWindowMonitor(window,nullptr,mode->width/2-1280/2,mode->height/2-720/2,1280,720,0);
            size.x=1280;size.y=720;
        }
        glViewport(0,0,size.x,size.y);
        Screenmanager::recalculate_screenview();
    }
    void setIcon(vector2<uint32> size,uint8 *pixels){
        GLFWimage ico;
        ico.height=size.y;ico.width=size.x;ico.pixels=pixels;
        glfwSetWindowIcon(window,1,&ico);
    }
}
