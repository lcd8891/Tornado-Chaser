#include <GL/gl.h>
#include <lite3D/glutils.hpp>

namespace LiteGL{
    void clearColor(float r,float g,float b,float a){
        glClearColor(r,g,b,a);
    }
    void setParam(GL_Param _param,bool enable){
        switch(_param){
            case GL_Param::Blend:
            if(enable){
                glEnable(0x0BE2);
            }else{
                glDisable(0x0BE2);
            }
            break;
            case GL_Param::CullFace:
            if(enable){
                glEnable(0x0B44);
            }else{
                glDisable(0x0B44);
            }
            break;
            case GL_Param::DepthTest:
            if(enable){
                glEnable(0x0B71);
            }else{
                glDisable(0x0B71);
            }
            break;
        }
    }
    void cullface(CullFace _cullface){
        switch(_cullface){
            case CullFace::Front:
            glCullFace(0x404);
            break;
            case CullFace::Back:
            glCullFace(0x405);
            break;
            case CullFace::Both:
            glCullFace(0x408);
            break;
        }
    }
    void frontface(FrontFace _frontface){
        switch(_frontface){
            case FrontFace::ClockWise:
            glFrontFace(0x900);
            break;
            case FrontFace::CounterClockWise:
            glFrontFace(0x901);
            break;
        }
    }
    void clear(bool depth){
        glClear((depth) ? 0x4000 | 0x100 : 0x4000);
    }
}