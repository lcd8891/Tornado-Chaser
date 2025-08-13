#include <freetype2/ft2build.h>
#include "./font.hpp"
#include <lite3D/glutils/texture.hpp>
#include <fstream>
#include <GL/gl.h>
#include "../buffer/loc_buffer.hpp"
#include FT_FREETYPE_H

#define FONT_ATLAS_SIZE 2048

struct CharMeta;

namespace{
    FT_Library ft;
}

struct Locale{
    uint16 charCount;
    uint32 charPos;
};

namespace FontLoader{
    std::map<int,CharMeta> charMap;
    void initialize(){
        if(FT_Init_FreeType(&ft)){
            throw EXIT_INFO("Couldn't initialize freetype library!");
        }
    }
    void updateLocale(std::string _locale){
        Locale locale = {0,0};
        if(_locale!="english"){
            std::ifstream file("./res/locale/"+_locale+".loc",std::ios::binary);
            if(!file.is_open())throw EXIT_INFO("couldn't load locale file");
            file.read(reinterpret_cast<char*>(&locale.charCount),sizeof(uint16));
            file.read(reinterpret_cast<char*>(&locale.charPos),sizeof(uint32));
            file.close();
        }
        FT_Face face;
        if(FT_New_Face(ft,"./res/font.ttf",0,&face)){
            throw EXIT_INFO("couldn't load font!");
        }
        FT_Set_Pixel_Sizes(face,0,CHAR_SIZE);
        unsigned char *atlasData = new unsigned char[FONT_ATLAS_SIZE*FONT_ATLAS_SIZE];
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
            ch.tex_position = {(float)pos.x/FONT_ATLAS_SIZE,(float)pos.y/FONT_ATLAS_SIZE};
            ch.tex_size = {(float)bitmap.width/FONT_ATLAS_SIZE,(float)bitmap.rows/FONT_ATLAS_SIZE};
            ch.size = {bitmap.width,bitmap.rows};
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
            ch.tex_position = {(float)pos.x/FONT_ATLAS_SIZE,(float)pos.y/FONT_ATLAS_SIZE};
            ch.tex_size = {(float)bitmap.width/FONT_ATLAS_SIZE,(float)bitmap.rows/FONT_ATLAS_SIZE};
            ch.size = {bitmap.width,bitmap.rows};
            ch.bearing = {face->glyph->bitmap_left,face->glyph->bitmap_top};
            ch.advance = face->glyph->advance.x;
            charMap[c] = ch;
            pos.x += bitmap.width+1;
            maxrow = std::max(maxrow,(int)bitmap.rows+1);
        }
        FT_Done_Face(face);
        Logger::info("locale updated to "+_locale);
        TextureBuffer::setTexture("glyph_atlas",new Texture(atlasData,{FONT_ATLAS_SIZE,FONT_ATLAS_SIZE},GL_RED));
    }
    void cleanup(){
        FT_Done_FreeType(ft);
    }
}