#pragma once


namespace Event{
    extern unsigned int char_input;
    extern bool focused;
    void initialize();
    void pollEvents();
    bool key(int keycode);
    bool keyp(int keycode);
    bool mouse_button(int button);
    bool mouse_buttonp(int button);
}