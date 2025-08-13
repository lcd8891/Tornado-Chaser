#include "lite3d.hpp"
#include <lite3D/lite_window.hpp>
#include "gameldr/gameldr.hpp"
#include "args.hpp"
#include <string>
#include <SFML/Graphics/Image.hpp>
#include <lite3D/lite_buffer.hpp>
#include "./graphics/font.hpp"

#define ENGINE_VERSION 1

namespace{

    void process_f1(){
        if(Event::keyp(KBKey::Q)){
            Window::close();
            Logger::waning("forced terminate!");
        }
        if(Event::keyp(KBKey::BACKSLASH)){
            Logger::error("force exception!");
            throw EXIT_INFO("Forced exception!");
        }
    }

    void loop(){
        while(!Window::isClose()){
            Event::pollEvents();
            if(Event::key(KBKey::F1)){
                process_f1();
            }
            LITE3D_GAME::on_frame();
            Window::display();
            Window::updateFPS();
        }
    }

    void loadloop(){
        
    }

    void set_icon(){
        sf::Image ico;
        if(ico.loadFromFile("./res/icon.png")){
            Window::setIcon({ico.getSize().x,ico.getSize().y},const_cast<unsigned char*>(ico.getPixelsPtr()));
        }else{
            Logger::waning("Icon doesn't loaded!");
        }
    }
}

namespace Lite3D{
    void start(){
        //Initalize state
        Logger::initialize();
        Logger::open_file();
        Logger::info("LLITE3D version "+std::to_string(ENGINE_VERSION));
        GameLDR::loadgame(Args::gamecomp);
        Logger::info("Game loaded from library!");
        Window::initialize("Lite3D",{1280,720});
        Event::initialize();
        Logger::info("Window initialized");
        FontLoader::initialize();
        Logger::info("FontLoader initialized");
        set_icon();
        LITE3D_GAME::on_initialize();
        loop();
        LITE3D_GAME::on_exit();
        terminate();
    }
    void terminate(){
        Logger::info("Shutting down");
        GameLDR::unload();
        Window::terminate();
        ShaderBuffer::delete_all();
        TextureBuffer::delete_all();
    }
}