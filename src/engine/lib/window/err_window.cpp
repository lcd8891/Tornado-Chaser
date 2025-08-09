#include <lite3D/lite_error.hpp>

#ifdef _WIN32
#include <windows.h>
#include <locale>
#include <codecvt>
#endif
#include <cstdlib>

namespace Lite3D{
    void show_error(std::string _text){
        #ifdef _WIN32    
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wtext;
        wtext+=L"Runtime error:\n";
        wtext+=converter.from_bytes(_text);
        wtext+=L"\n\nExecution terminated!";
        int result = MessageBoxW(
            NULL,
            wtext.c_str(),
            L"Lite3D error!",
            MB_ICONERROR | MB_OK
        );
        #else
        system(("zenity --error --title=\"Lite3D error!\" --text=\"Runtime error:\n"+_text+"\n\nExecution terminated!\"").c_str());
        #endif
    }
}