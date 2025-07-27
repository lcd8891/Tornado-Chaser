#include "event.hpp"
#include "../vector.hpp"
#include "../types.hpp"
#include "window.hpp"
#include "cstring"
#include <map>
#include "../graphics/screenmanager.hpp"

#define _MOUSE_BUTTONS 1024

namespace{
    bool* _keys;
    uint32* _frames;
    uint32 _current;
    bool _cursor_started;
}

namespace Event{
    vector2<int16> mouse_pos; 
    vector2<int16> mouse_delta;
    int8 mwheel_delta;
    uint32 char_input;
    bool focused;

    void window_size_callback(GLFWwindow* window, int width, int height){
        Window::size.x = width;
        Window::size.y = height;
        glViewport(0,0,width,height);
        Screenmanager::recalculate_screenview();
    }
    void cursor_position_callback(GLFWwindow* window,double xpos,double ypos){
        if(_cursor_started){
            mouse_delta.x+=xpos-mouse_pos.x;
            mouse_delta.y+=ypos-mouse_pos.y;
        }else{
            _cursor_started = true;
        }
        mouse_pos.x=xpos;
        mouse_pos.y=ypos;
    }
    void window_focus_callback(GLFWwindow *window,int focused){
        Event::focused = focused;
    }
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
        if (action == GLFW_PRESS){
            _keys[_MOUSE_BUTTONS+button] = true;
            _frames[_MOUSE_BUTTONS+button] = _current;
        }
        else if (action == GLFW_RELEASE){
            _keys[_MOUSE_BUTTONS+button] = false;
            _frames[_MOUSE_BUTTONS+button] = _current;
        }
    }
    void key_callback (GLFWwindow* window,int key, int scancode, int action, int mode){
        if(action==GLFW_PRESS){
            _keys[key]=true;
            _frames[key]=_current;
        }else if(action==GLFW_RELEASE){
            _keys[key]=false;
            _frames[key]=_current;
        }
    }
    void mouse_scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
        mwheel_delta = yoffset;
    }
    void char_callback(GLFWwindow *window, uint32 character){
        char_input=character;
    }

    void initialize(){
        _frames = new uint32[1032];
        _keys = new bool[1032];

        memset(_frames,0,sizeof(uint32)*1032);
        memset(_keys,false,sizeof(bool)*1032);

        glfwSetWindowFocusCallback(Window::window,window_focus_callback);
        glfwSetWindowSizeCallback(Window::window,window_size_callback);
        glfwSetMouseButtonCallback(Window::window,mouse_button_callback);
        glfwSetCursorPosCallback(Window::window,cursor_position_callback);
        glfwSetKeyCallback(Window::window,key_callback);
        glfwSetScrollCallback(Window::window,mouse_scroll_callback);
        glfwSetCharCallback(Window::window,char_callback);
    }
    void pollEvents(){
        mouse_delta = {0,0};
        mwheel_delta = 0;
        char_input = 0;
        glfwPollEvents();
    }
    bool key(int keycode){
        if(keycode<0 || keycode>= _MOUSE_BUTTONS)return false;
        return _keys[keycode];
    }

    bool keyp(int keycode){
        if(keycode<0 || keycode>= _MOUSE_BUTTONS)return false;
        return _keys[keycode] && _frames[keycode] == _current;
    }

    bool mouse_button(int button){
        int index = _MOUSE_BUTTONS+button;
        return _keys[index];
    }

    bool mouse_buttonp(int button){
        int index = _MOUSE_BUTTONS+button;
        return _keys[index] && _frames[index] == _current;
    }
}
