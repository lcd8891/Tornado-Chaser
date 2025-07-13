#pragma once
#include <GLFW/glfw3.h>

template<typename T>
struct vector2;

using uint16 = unsigned short;

namespace Window{
    extern GLFWwindow *window;
    extern vector2<uint16> size;
    extern bool mouse_locked;
    extern bool fullscreen;
    void initialize(std::string _name, vector2<uint16> _size);
    void close();
    bool isClose();
    void display();
    void lockMouse(bool locked);
    void terminate();
    void setMouseType(int type);
    void setFullscreen(bool _fullscreen);
}