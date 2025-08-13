#pragma once
#include <string>
#include <vector>
#include "./screenitems.hpp"

class Screen{
    public:
    bool background;
    bool lockmouse;
    std::vector<ScreenItem*> items;
    Screen(bool _background = true, bool _lockmouse = false);
    ~Screen();
    void addItem(ScreenItem* _item);
};

namespace ScreenManager{
    void setScreen(std::string _i);
    Screen* getCurrentScreen();
    void draw();
}