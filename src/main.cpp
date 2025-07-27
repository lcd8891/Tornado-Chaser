#include "types.hpp"
#include <fstream>
#include <iomanip>
#include "other/time.hpp"
#include "other/logger.hpp"
#include "game.hpp"

int main(){
    Logger::initialize();
    Logger::open_file();
    try{
        Lite3D::start();
    }catch(const EXIT_INFO &ei){
        Logger::terminate(ei);
        Lite3D::terminate();
        return ei.code;
    }
    return 0;
}