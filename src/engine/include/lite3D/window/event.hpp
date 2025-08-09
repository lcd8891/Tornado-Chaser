#pragma once
#include <lite3D/lite_utils.hpp>


namespace Event{
    extern vector2<int16> mouse_pos; 
    extern vector2<int16> mouse_delta;
    extern int8 mwheel_delta;
    extern uint32 char_input;
    extern bool focused;
    void initialize();
    void pollEvents();
    bool key(int keycode);
    bool keyp(int keycode);
    bool mouse(int button);
    bool mousep(int button);
}