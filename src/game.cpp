#include "game.hpp"
#include "window/window.hpp"
#include "window/event.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"
#include "graphics/font.hpp"
#include "vector.hpp"
#include "types.hpp"
#include <string>
#include <SFML/Graphics/Image.hpp>
#include <filesystem>
#include "other/logger.hpp"

namespace{

    void render_game(){
        
    }
}

namespace Lite3D{   
    void terminate(){
        Font::cleanup();
        Window::terminate();
    }

    void f1_functions(){
        if(Event::keyp(GLFW_KEY_T)){
            if(std::filesystem::exists("./export")){std::filesystem::create_directory("./export");}
            Font::export_texture();
            Logger::info("Atlases exported successfully!");
        }
    }

    void startCycle(){
        while(!Window::isClose()){
            Event::pollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if(Event::key(GLFW_KEY_F1))f1_functions();
            render_game();
            Window::display();
        }
    }

    void initRes(){
        Font::initialize();
        Logger::info("Text renderer initialized!");
        Font::updateLocale("russian");
        //Screenmanager::initialize();
        Logger::info("Shader loaded!");
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