#include "args.hpp"
#include <cstring>

namespace Args{
    bool cmd = false;
    std::string gamecomp = "lite3d_game";
    void parse(int argc, char** argv){
        for(int i = 1;i<argc;i++){
            if(std::string(argv[i])=="--cmd"){
                cmd = true;
            }
            if(strncmp(argv[i], "--game=", 7) == 0){
                gamecomp = std::string(argv[i]).substr(7);
            }
        }
    }
}