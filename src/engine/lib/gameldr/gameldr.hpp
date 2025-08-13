#pragma once 
#include <string>

namespace LITE3D_GAME{
    extern void (*on_initialize)();
    extern void (*on_frame)();
    extern void (*on_exit)();
}

namespace GameLDR{
    void loadgame(std::string name);
    void unload();
}