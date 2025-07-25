#pragma once
#include <GLFW/glfw3.h>
#include <string>

template<typename T>
struct vector2;

using uint16 = unsigned short;
using uint8 = unsigned char;
using uint32 = unsigned int;

namespace Window{
    extern GLFWwindow *window;
    extern vector2<uint16> size;
    extern bool mouse_locked;
    extern bool fullscreen;
    extern bool focus;
    void initialize(std::string _name, vector2<uint16> _size);
    void close();
    bool isClose();
    void display();
    void lockMouse(bool locked);
    void terminate();
    void setMouseType(int type);
    void setFullscreen(bool _fullscreen);
    void setIcon(vector2<uint32> size,uint8 *pixels);
}