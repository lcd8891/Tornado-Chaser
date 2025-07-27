#pragma once
#include <vector>
#include "screenelements.hpp"

struct Screen{
    std::vector<Elements> elements;
    unsigned int ID;
    bool lockmouse;
    bool background;

    Screen(unsigned int _ID,bool _lockmouse,bool _background);
    void AddElement(Elements el);
};