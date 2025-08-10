#pragma once

#include "glutils/mesh.hpp"
#include "glutils/shader.hpp"
#include "glutils/texture.hpp"

enum class GL_Param{
    Blend,
    CullFace,
    DepthTest
};
enum class CullFace{
    Front,
    Back,
    Both
};
enum class FrontFace{
    ClockWise,
    CounterClockWise
};
namespace LiteGL{
    void clearColor(float r,float g,float b,float a = 1.f);
    void setParam(GL_Param _param,bool enable);
    void cullface(CullFace _cullface = CullFace::Back);
    void frontface(FrontFace _frontface = FrontFace::ClockWise);
    void clear(bool depth = false);
}