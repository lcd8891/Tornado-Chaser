#include "lite3d.hpp"
#include <lite3D/lite_utils.hpp>
#include <lite3D/lite_error.hpp>
#include "args.hpp"

int main(int argc,char** argv){
    Args::parse(argc,argv);
    try{
        Lite3D::start();
    }catch(const EXIT_INFO &ei){
        Lite3D::show_error(ei.info);
        Logger::terminate(ei);
        Lite3D::terminate();
        return 1;
    }
    return 0;
}