#include "texture.hpp"
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include "../types.hpp"

Texture::Texture(unsigned int _ID):ID(_ID){}
Texture::~Texture(){
    glDeleteTextures(1,&ID);
}
void Texture::use(){
    glBindTexture(0xDE1,ID);
}
Texture* loadFromFile(std::string _str){
    sf::Image image;if(image.loadFromFile(_str)){throw EXIT_INFO("Couldn't load texture!",10);}
    GLuint id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.getSize().x,image.getSize().y,
                0, GL_RGBA,GL_UNSIGNED_BYTE,image.getPixelsPtr()
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return new Texture(id);
}
Texture* loadFromMemory(void *_data,size_t _size){
    sf::Image image;if(image.loadFromMemory(_data,_size)){throw EXIT_INFO("Couldn't load texture!",10);}
    GLuint id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.getSize().x,image.getSize().y,
                0, GL_RGBA,GL_UNSIGNED_BYTE,image.getPixelsPtr()
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return new Texture(id);
}