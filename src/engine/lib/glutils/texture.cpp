#include <lite3D/glutils/texture.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include <lite3D/lite_utils.hpp>

Texture::Texture(unsigned int _ID):ID(_ID){}
Texture::~Texture(){
    glDeleteTextures(1,&ID);
}
Texture::Texture(void *pixdata, vector2<uint32> size,int colormode,bool linear){
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage2D(GL_TEXTURE_2D,0,colormode,size.x,size.y,0,GL_RGBA,GL_UNSIGNED_BYTE,pixdata);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (linear) ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (linear) ? GL_LINEAR : GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::use(){
    glBindTexture(0xDE1,ID);
}
Texture* loadFromFile(std::string _str){
    sf::Image image;if(image.loadFromFile(_str)){throw EXIT_INFO("Couldn't load texture!");}
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
    sf::Image image;if(image.loadFromMemory(_data,_size)){throw EXIT_INFO("Couldn't load texture!");}
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