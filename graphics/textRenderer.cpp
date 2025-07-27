#include "textRenderer.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <vector>
#include <freetype2/ft2build.h>
#include <map>
#include <GL/glew.h>
#include <cstring>
#include <cmath>
#include <fstream>
#include FT_FREETYPE_H   
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"
#include "screenmanager.hpp"
#include "../other/logger.hpp"

#define FONT_ATLAS_SIZE 1024
#define CHAR_SIZE 64

struct Text{
    vector2<int> position;
    uint8 scale;
    std::string str;
};

struct CharMeta{
    vector2<float> position;
    vector2<float> size;
    vector2<int> bearing;
    float advance;
};

struct Locale{
    uint16 charCount;
    uint32 charPos;
};

namespace{
    const int attrs[] = {2,2,2,3,0};
    Shader *textShader;
    std::vector<Text> textes;
    std::map<uint32,CharMeta> charMap;
    FT_Library ft;
    Texture *font_atlas;
    Mesh *mesh;
}

namespace TextRenderer{
    void initialize(){
        textShader = initShaderFromFile("./res/shaders/textShader.vert","./res/shaders/textShader.frag","./res/shaders/textShader.geom");
        if(FT_Init_FreeType(&ft)){
            throw EXIT_INFO("couldn't initialize freetype!",8);
        }
    }
    void updateLocale(std::string _locale){
        Locale locale = {0,0};
        if(_locale!="english"){
            std::ifstream file("./res/locale/"+_locale+".loc",std::ios::binary);
            if(!file.is_open())throw EXIT_INFO("couldn't load locale file",11);
            file.read(reinterpret_cast<char*>(&locale.charCount),sizeof(uint16));
            file.read(reinterpret_cast<char*>(&locale.charPos),sizeof(uint32));
            file.close();
        }
        FT_Face face;
        if(FT_New_Face(ft,"./res/font.ttf",0,&face)){
            throw EXIT_INFO("couldn't load font!",9);
        }
        FT_Set_Pixel_Sizes(face,0,CHAR_SIZE);
        GLbyte *atlasData = new GLbyte[FONT_ATLAS_SIZE*FONT_ATLAS_SIZE];
        memset(atlasData,0,FONT_ATLAS_SIZE*FONT_ATLAS_SIZE);
        vector2<int> pos = {0,0};
        int maxrow = 0;
        //ENGLISH CHARS
        for(uint32 c = 0;c<128;c++){
            if(FT_Load_Char(face,c,FT_LOAD_RENDER))continue;
            FT_Bitmap bitmap = face->glyph->bitmap;
            if(pos.x+bitmap.width >= FONT_ATLAS_SIZE){
                pos.x = 0;pos.y += maxrow;
                maxrow=0;
            }
            if(pos.y+bitmap.rows >= FONT_ATLAS_SIZE){
                break;
            }
            for(int row = 0;row < bitmap.rows;row++){
                for(int col = 0;col < bitmap.width;col++){
                    unsigned char value = bitmap.buffer[row*bitmap.width+col];
                    int index = ((pos.y+row)*FONT_ATLAS_SIZE+(pos.x+col));
                    atlasData[index]=value;
                }
            }
            CharMeta ch;
            ch.position = {(float)pos.x/FONT_ATLAS_SIZE,(float)pos.y/FONT_ATLAS_SIZE};
            ch.size = {(float)bitmap.width/FONT_ATLAS_SIZE,(float)bitmap.rows/FONT_ATLAS_SIZE};
            ch.bearing = {face->glyph->bitmap_left,face->glyph->bitmap_top};
            ch.advance = face->glyph->advance.x;
            charMap[c] = ch;
            pos.x += bitmap.width+1;
            maxrow = std::max(maxrow,(int)bitmap.rows+1);
        }
        //FROM LOCALE.loc
        for(uint32 c = locale.charPos;c<locale.charPos+locale.charCount;c++){
            if(FT_Load_Char(face,c,FT_LOAD_RENDER))continue;
            FT_Bitmap bitmap = face->glyph->bitmap;
            if(pos.x+bitmap.width >= FONT_ATLAS_SIZE){
                pos.x = 0;pos.y += maxrow;
                maxrow=0;
            }
            if(pos.y+bitmap.rows >= FONT_ATLAS_SIZE){
                break;
            }
            for(int row = 0;row < bitmap.rows;row++){
                for(int col = 0;col < bitmap.width;col++){
                    unsigned char value = bitmap.buffer[row*bitmap.width+col];
                    int index = (pos.y+row)*FONT_ATLAS_SIZE+(pos.x+col);
                    atlasData[index]=value;
                }
            }
            CharMeta ch;
            ch.position = {(float)pos.x/FONT_ATLAS_SIZE,(float)pos.y/FONT_ATLAS_SIZE};
            ch.size = {(float)bitmap.width/FONT_ATLAS_SIZE,(float)bitmap.rows/FONT_ATLAS_SIZE};
            ch.bearing = {face->glyph->bitmap_left,face->glyph->bitmap_top};
            ch.advance = face->glyph->advance.x;
            charMap[c] = ch;
            pos.x += bitmap.width+1;
            maxrow = std::max(maxrow,(int)bitmap.rows+1);
        }
        FT_Done_Face(face);
        GLuint tex;
        glGenTextures(1,&tex);
        glBindTexture(GL_TEXTURE_2D,tex);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                FONT_ATLAS_SIZE,
                FONT_ATLAS_SIZE,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                atlasData
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        delete[] atlasData;
        Logger::info("locale updated to "+_locale);
        font_atlas = new Texture(tex);
    }
    void draw(){
        //textShader->use();
        font_atlas->use();
        //textShader->uniformMatrix("view",Screenmanager::getScreenView());
        //mesh->draw(GL_TRIANGLES);
    }
    void export_texture(){
        font_atlas->use();
        GLint width, height;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        GLint internalFormat;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
        GLenum format = GL_RGBA;
        int channels = 4;
        if(internalFormat == GL_RGB || internalFormat == GL_RGB8) {
            format = GL_RGB;
            channels = 3;
        } else if(internalFormat == GL_RGBA || internalFormat == GL_RGBA8) {
            format = GL_RGBA;
            channels = 4;
        } else if(internalFormat == GL_RED || internalFormat == GL_R8) {
            format = GL_RED;
            channels = 1;
        }
        std::vector<GLubyte> pixels(width * height * channels);
        glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, pixels.data());
        stbi_write_png("./export/font.png", width, height, channels, pixels.data(), width * channels);
    }
    void cleanup(){
        delete textShader;
        FT_Done_FreeType(ft);
    }
}