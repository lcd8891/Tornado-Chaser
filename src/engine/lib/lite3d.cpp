#include "lite3d.hpp"
#include <lite3D/lite_window.hpp>
#include "gameldr/gameldr.hpp"
#include "args.hpp"
#include <string>
#include <SFML/Graphics/Image.hpp>

#define ENGINE_VERSION 1

namespace{

    void process_f1(){
        if(Event::keyp(GLFW_KEY_Q)){
            Window::close();
        }
    }

    void loop(){
        while(!Window::isClose()){
            Event::pollEvents();
            if(Event::key(GLFW_KEY_F1)){
                process_f1();
            }
            LITE3D_GAME::on_frame();
            Window::display();
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
        set_icon();
        loop();
        LITE3D_GAME::on_exit();
        terminate();
    }
    void terminate(){
        GameLDR::unload();
        Window::terminate();
    }
}