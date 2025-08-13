#pragma once
#include <string>

class Screen;

namespace ScreenBuffer{
    //Screen* load_from_res(std::string _path,std::string _i);
    void load_from_mem(std::string _i, Screen* _scr);
    Screen* get(std::string _i);
    void delete_screen(std::string _i);
    void delete_all();
}