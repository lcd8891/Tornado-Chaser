#include <lite3D/lite_window.hpp>
#include <lite3D/glutils.hpp>
#include <lite3D/lite_buffer.hpp>
#include <string>
#include <glm/matrix.hpp>

namespace{
    Mesh* mesh;
    Shader* shader;
}

extern "C" void game_on_initialize(){
    Window::setTitle("Tornado Chaser");
    LiteGL::clearColor(0.2,0.2,0.2);
    LiteGL::setParam(GL_Param::CullFace,false);
    LiteGL::setParam(GL_Param::DepthTest,false);
    float vertices[] = {
        0,0,0,
        1,0,0,
        0,1,0
    };
    int attrs[] = {3,0};
    mesh = new Mesh(vertices,3,attrs);
    shader = ShaderBuffer::load_from_res("shader","main");
}//When engine has been initalized.

extern "C" void game_on_frame(){
    LiteGL::clear();
    shader->use();
    mesh->draw(Primitive::Triangles);
}//Before engine show frame.

extern "C" void game_on_exit(){
    
}//Before engine finalize.