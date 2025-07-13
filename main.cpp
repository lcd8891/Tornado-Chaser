#include "types.hpp"
#include <fstream>
#include <iomanip>
#include "other/time.hpp"
#include "game.hpp"

void writeExitToFile(const EXIT_INFO info){
    Time t = getCurrentTime();
    std::string path = "crash_"+std::to_string(t.year)+"_"+std::to_string(t.month)+"_"+std::to_string(t.day)+"_"+std::to_string(t.hour)+"_"+std::to_string(t.minute)+"_"+std::to_string(t.second)+".info";
    std::ofstream file(path);
    file << info.info << '\n';
    file << "Exit code: 0x" << std::setfill('0') << std::setw(8) << std::hex << info.code;
}

int main(){
    try{
        Lite3D::start();
    }catch(const EXIT_INFO &ei){
        writeExitToFile(ei);
        Lite3D::terminate();
        return ei.code;
    }
    return 0;
}