#include <SFML/Network.hpp>
#include <iostream>

int main(){
    sf::TcpListener listener;
    if(listener.listen(2556)!=sf::Socket::Done){
        std::cerr << "Couldn't create listener!" << std::endl;
        return 1;
    }
    sf::TcpSocket socket;
    std::cout << "Opened server at 2556" << std::endl;
    std::cout << "Waiting for connect..." << std::endl;
    if(listener.accept(socket)!=sf::Socket::Done){
        std::cerr << "Couldn't connect to client!" << std::endl;
        return 2;
    }
    std::cout << "Connected: " << socket.getRemoteAddress() << std::endl;
    sf::Packet packet;
    short x,y;
    sf::Socket::Status status = sf::Socket::NotReady;
    while(status!=sf::Socket::Disconnected){
        status = socket.receive(packet);
        if( status==sf::Socket::Done && (packet >> x >> y)){
            std::cout << "Clicked at " << x << "x" << y << std::endl;
        }else{
            std::cerr << "Couldn't parse packet! (" << packet.getDataSize() << ")" << std::endl;
        }
    }
    std::cout << "Disconnected!" << std::endl;
    return 0;
}