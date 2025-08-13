#include <lite3D/gui/screen.hpp>
#include <lite3D/glutils.hpp>
#include <lite3D/lite_buffer.hpp>
#include <lite3D/buffers/screenbuffer.hpp>
#include "../graphics/font.hpp"
#include <glm/ext.hpp>
#include <lite3D/lite_window.hpp>

namespace{
    Shader *textShader;
    Mesh *textMesh;
    // DynamicMesh *dtextMesh;
    std::vector<ItemMeta> textMeta;
    //std::vector<uint32> dtextIndex;
    int attrs_text_mesh[] = {3,2,3,0};

    Screen *current;
}

Screen::Screen(bool _background, bool _lockmouse):background(_background),lockmouse(_lockmouse){}
Screen::~Screen(){
    for(auto* it : items){
        delete it;
    }
}
void Screen::addItem(ScreenItem* _item){
    items.push_back(_item);
}

ScreenItem::ScreenItem(vector2<int> _position,int8 _layer,vector3<uint8> _color):position(_position),layer(_layer),color(_color){}
void ScreenItem::genMesh(std::vector<float> &_vertices){
    static_assert(true,"using screenitem default genMesh functions!");
}
    
namespace ScreenItems{
    StaticText::StaticText(vector2<int> _position,std::string _str, vector3<uint8> _color,int8 _layer):ScreenItem(_position,_layer,_color),str(_str){}
    void StaticText::genMesh(std::vector<float> &_vertices){
        ItemMeta itemMeta;
        itemMeta.position = _vertices.size();
        int x = 0;
        int y = 0;
        for(int ch : str){
            if(ch == '\n'){
                y+=CHAR_SIZE;
                continue;
            }
            CharMeta meta = FontLoader::charMap[ch];
            _vertices.insert(_vertices.end(),{(float)x + (float)meta.bearing.x,(float)y + (float)meta.bearing.y,(float)layer,meta.tex_position.x,meta.tex_position.y,color.x / 255.f,color.y / 255.f,color.z / 255.f});
            _vertices.insert(_vertices.end(),{(float)x + (float)meta.bearing.x + (float)meta.size.x,(float)y + (float)meta.bearing.y + (float)meta.size.y,(float)layer,meta.tex_position.x+meta.tex_size.x,meta.tex_position.y+meta.tex_size.y,color.x / 255.f,color.y / 255.f,color.z / 255.f});
        }
        itemMeta.size = _vertices.size() - itemMeta.position;
        itemMeta.pos_mat = glm::translate(glm::mat4(1.f),glm::vec3(position.x,position.y,layer));
        
        textMeta.push_back(itemMeta);
    }
    DynamicText::DynamicText(vector2<int> _position, std::string *_str, vector3<uint8> _color,int8 _layer):ScreenItem(_position,_layer,_color),str(_str){}
    Rect::Rect(vector2<int> _position, vector2<uint32> _size,vector3<uint8> _color,int8 _layer):ScreenItem(_position,_layer,_color),size(_size){}
    Line::Line(vector2<int> _position1, vector2<int> _position2,vector3<uint8> _color,int8 _layer):ScreenItem(_position1,_layer,_color),position2(_position2){}
    UI_Container::UI_Container(vector2<int> _default_position, vector2<uint32> _default_size,vector3<uint8> _color,int8 _layer):ScreenItem(_default_position,_layer,_color),default_size(_default_size){}
}

namespace ScreenManager{
    void initialize(){
        textShader = initShaderFromFile("./res/shaders/textShader.vert","./res/shaders/textShader.frag"/*,"./res/shaders/textShader.geom"*/);
    }
    void update(){

    }
    void setScreen(std::string _i){
        current = ScreenBuffer::get(_i);
        if(!current){
            throw EXIT_INFO("couldn't load screen: "+_i);
        }
    }
    Screen* getCurrentScreen(){
        return current;
    }
    void draw(){
        textShader->use();
        textShader->uniformMatrix("view",Window::getView());
        for(ItemMeta itemmeta : textMeta){
            textShader->uniformMatrix("model",itemmeta.pos_mat);
            textMesh->draw_part(Primitive::Lines,itemmeta.size,itemmeta.position);
        };
    }
    void finalize(){

    }
}