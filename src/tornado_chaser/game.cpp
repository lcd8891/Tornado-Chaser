#include <lite3D/lite_window.hpp>
#include <lite3D/glutils.hpp>
#include <lite3D/lite_buffer.hpp>
#include <string>
#include <glm/matrix.hpp>
#include <lite3D/graphics/camera.hpp>
namespace{
    Mesh* mesh;
    Shader* shader;
    Camera* camera;
    float cam[2] = {0.f,0.f};
    float speed = 5.f;
    std::string *text = new std::string("FPS: -");
}

extern "C" void game_on_initialize(){
    Window::setTitle("Tornado Chaser");
    LiteGL::clearColor(0.2,0.2,0.2);
    LiteGL::setParam(GL_Param::CullFace,true);
    LiteGL::setParam(GL_Param::DepthTest,false);
    float vertices[] = {
        0,0,0,
        1,0,0,
        0,1,0,
        1,0,0,
        0,1,0,
        1,1,0,
        0,1,0,
        1,1,0,
        0,1,1
    };
    int attrs[] = {3};
    mesh = new Mesh(vertices,9,attrs);

    shader = ShaderBuffer::load_from_res("shader","main");
    camera = new Camera({-2,0,0});
	cam[1]=glm::radians(180.f);
	camera->rotate({cam[0],cam[1],0});
    camera->setFOV(90);

    //Screen* scr = new Screen(false,true);
    //->addItem(new ScreenItems::StaticText({10,10},"sample text"));
    //ScreenBuffer::load_from_mem("default",scr);
    //ScreenManager::setScreen("default");
    *text = "a";
}//When engine has been initalized.

extern "C" void game_on_frame(){
    //*text = "FPS: " + std::to_string(FPSCounter::fps);
    Window::setTitle("FPS: " + std::to_string(FPSCounter::fps));
    if(Event::key(KBKey::W)){
        camera->position += camera->dir * glm::vec3(FPSCounter::delta * speed);
    }
    if(Event::key(KBKey::S)){
        camera->position -= camera->dir * glm::vec3(FPSCounter::delta * speed);
    }
    if(Event::key(KBKey::D)){
        camera->position += camera->right * glm::vec3(FPSCounter::delta * speed);
    }
    if(Event::key(KBKey::A)){
        camera->position -= camera->right * glm::vec3(FPSCounter::delta * speed);
    }
    if(Event::key(KBKey::SPACE)){
        camera->position += glm::vec3(0,FPSCounter::delta * speed,0);
    }
    if(Event::key(KBKey::LEFT_SHIFT)){
        camera->position -= glm::vec3(0,FPSCounter::delta * speed,0);
    }
    if(Event::keyp(KBKey::TAB)){
        Window::mouse_locked=!Window::mouse_locked;
        Window::lockMouse(Window::mouse_locked);
    }
    if(Window::mouse_locked){
        cam[1] += -Event::mouse_delta.x / (float)Window::size.x;
        cam[0] += -Event::mouse_delta.y / (float)Window::size.y;
		camera->rotation = glm::mat4(1.0);
		camera->rotate({cam[0],cam[1],0});
    }
    LiteGL::clear();
    shader->use();
    shader->uniformMatrix("view",camera->getProjection() * camera->getView());
    mesh->draw(Primitive::Triangles);
    //ScreenManager::draw();
}//Before engine show frame.

extern "C" void game_on_exit(){
    
}//Before engine finalize.