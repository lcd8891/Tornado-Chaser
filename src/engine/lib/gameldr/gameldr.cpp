#include "gameldr.hpp"
#include <filesystem>

#ifdef _WIN32
#include "windows.h"
#else
#include "dlfcn.h"
#endif  

#ifdef _WIN32
#define LIB_FORMAT ".dll"
#else
#define LIB_FORMAT ".so"
#endif

#include <lite3D/lite_utils.hpp>

namespace LITE3D_GAME{
    void (*on_initialize)();
    void (*on_frame)();
    void (*on_exit)();
}

namespace GameLDR{
    #ifdef _WIN32
        static HMODULE handle = nullptr;
    #else
        static void* handle = nullptr;
    #endif
    void loadgame(std::string name){
        if(!std::filesystem::exists(name+LIB_FORMAT)){
            throw EXIT_INFO("Couldn't find file "+name+LIB_FORMAT);
        }
        #ifdef _WIN32
            handle = LoadLibraryA((name+LIB_FORMAT).c_str());
            if(!handle){
                throw EXIT_INFO("Couldn't load "+name+LIB_FORMAT);
            }
            LITE3D_GAME::on_initialize = (void(*)())GetProcAddress(handle,"game_on_initialize");
            LITE3D_GAME::on_frame = (void(*)())GetProcAddress(handle,"game_on_frame");
            LITE3D_GAME::on_exit = (void(*)())GetProcAddress(handle,"game_on_exit");
            if(!LITE3D_GAME::on_initialize && !LITE3D_GAME::on_frame && !LITE3D_GAME::on_exit){
                FreeLibrary(handle);
                throw EXIT_INFO("Couldn't find processes in "+name+LIB_FORMAT);
            }
        #else
            handle = dlopen(("./"+name+LIB_FORMAT).c_str(),RTLD_LAZY);
            if(!handle){
                throw EXIT_INFO("Couldn't load "+name+LIB_FORMAT+": "+dlerror());
            }
            LITE3D_GAME::on_initialize = (void(*)())dlsym(handle,"game_on_initialize");
            LITE3D_GAME::on_frame = (void(*)())dlsym(handle,"game_on_frame");
            LITE3D_GAME::on_exit = (void(*)())dlsym(handle,"game_on_exit");
            const char* dlsym_error = dlerror();
            if((!LITE3D_GAME::on_initialize && !LITE3D_GAME::on_frame && !LITE3D_GAME::on_exit) || dlsym_error){
                dlclose(handle);
                throw EXIT_INFO("Couldn't find processes in "+name+LIB_FORMAT);
            }
        #endif
    }
    void unload(){
        #ifdef _WIN32
            FreeLibrary(handle);
        #else
            dlclose(handle);
        #endif
    }
}