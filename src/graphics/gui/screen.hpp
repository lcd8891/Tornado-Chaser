#pragma once
#include <vector>
#include "screenelements.hpp"

struct Screen{
    std::vector<ScreenElement> elements;
    bool lockmouse;
    bool background;

    Screen();
    Screen(bool _lockmouse,bool _background);
    void AddElement(ScreenElement el);
};