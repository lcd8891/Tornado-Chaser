#include "game.hpp"
#include "window/window.hpp"
#include "window/event.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"
#include "graphics/textRenderer.hpp"
#include "graphics/screenmanager.hpp"
#include "vector.hpp"
#include "types.hpp"
#include <string>
#include <SFML/Graphics/Image.hpp>
#include <filesystem>
#include "other/logger.hpp"

namespace{
    Shader *shader;
    Mesh *mesh;
    
    void draw(){
        TextRenderer::draw();
        shader->use();
        shader->uniformMatrix("view",Screenmanager::screenView);
        mesh->draw(GL_TRIANGLES);
    }
}

namespace Lite3D{   
    void terminate(){
        TextRenderer::cleanup();
        Window::terminate();
    }

    void f1_functions(){
        if(Event::keyp(GLFW_KEY_T)){
            if(std::filesystem::exists("./export")){std::filesystem::create_directory("./export");}
            TextRenderer::export_texture();
            Logger::info("Atlases exported successfully!");
        }
    }

    void startCycle(){
        while(!Window::isClose()){
            Event::pollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if(Event::key(GLFW_KEY_F1))f1_functions();
            draw();
            Window::display();
        }
    }

    void initRes(){
        TextRenderer::initialize();
        Logger::info("Text renderer initialized!");
        TextRenderer::updateLocale("russian");
        shader = initShaderFromFile("./res/shaders/shader.vert","./res/shaders/shader.frag");
        Logger::info("Shader loaded!");
        float vertices[] = {
            200,200,1,1,1,0,0,
            700,200,1,1,1,1,0,
            200,700,1,1,1,0,1,

            200,700,1,1,1,0,1,
            700,200,1,1,1,1,0,
            700,700,1,1,1,1,1
        };
        int attrs[] = {2,3,2,0};
        mesh = new Mesh(vertices,6,attrs);
    }

    void start(){
        Logger::info("Tornado catcher. By lcd8891.");
        Logger::info("Initializing");
        Window::initialize("Tornado Chaser",vector2<int>(1280,720));
        Logger::info("Window created!");
        Event::initialize();
        Logger::info("Event registreted!");
        sf::Image ico;ico.loadFromFile("./res/icon.png");
        Window::setIcon({ico.getSize().x,ico.getSize().y},const_cast<uint8*>(ico.getPixelsPtr()));
        Logger::info("Initialized successfully!");
        initRes();
        startCycle();
    }
}