#include "game.hpp"
#include "window/window.hpp"
#include "vector.hpp"
#include "types.hpp"
#include <string>
#include <SFML/Graphics/Image.hpp>

namespace Lite3D{
    void terminate(){
        Window::terminate();
    }
    void start(){
        Window::initialize("Tornado Chaser",vector2<uint16>(1280,720));
        sf::Image ico;ico.loadFromFile("./res/icon.png");
        Window::setIcon({ico.getSize().x,ico.getSize().y},const_cast<uint8*>(ico.getPixelsPtr()));
    }
}