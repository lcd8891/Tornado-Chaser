#pragma once


namespace Event{
    extern unsigned int char_input;
    extern bool focused;
    void initialize();
    void pollEvents();
    bool key(int keycode);
    bool key_pressed(int keycode);
    bool mouse_button(int button);
    bool mouse_button_pressed(int button);
}