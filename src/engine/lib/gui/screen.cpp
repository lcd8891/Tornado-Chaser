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
    DynamicMesh *dtextMesh;
    std::vector<ItemMeta> textMeta,dtextMeta;
    std::vector<uint32> dtextIndex;
    int attrs_text_mesh[] = {2,2,3,0};
    Texture* glyph_atlas;

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
                x=0;
                continue;
            }
            CharMeta meta = FontLoader::charMap[ch];
            _vertices.insert(_vertices.end(),{(float)x + (float)meta.bearing.x,(float)y + (CHAR_SIZE - meta.bearing.y),meta.tex_position.x,meta.tex_position.y,color.x / 255.f,color.y / 255.f,color.z / 255.f});
            _vertices.insert(_vertices.end(),{(float)x + (float)meta.bearing.x + (float)meta.size.x,(float)y + (float)meta.size.y + (CHAR_SIZE - meta.bearing.y),meta.tex_position.x+meta.tex_size.x,meta.tex_position.y+meta.tex_size.y,color.x / 255.f,color.y / 255.f,color.z / 255.f});
            x += meta.advance;
        }
        itemMeta.size = _vertices.size() - itemMeta.position;
        itemMeta.pos_mat = glm::translate(glm::mat4(1.f),glm::vec3(position.x,position.y,layer));
        
        textMeta.push_back(itemMeta);
    }
    DynamicText::DynamicText(vector2<int> _position, std::string *_str, vector3<uint8> _color,int8 _layer):ScreenItem(_position,_layer,_color),str(_str){}
    void DynamicText::genMesh(std::vector<float> &_vertices){

    }
    Rect::Rect(vector2<int> _position, vector2<uint32> _size,vector3<uint8> _color,int8 _layer):ScreenItem(_position,_layer,_color),size(_size){}
    void Rect::genMesh(std::vector<float> &_vertices){

    }
    Line::Line(vector2<int> _position1, vector2<int> _position2,vector3<uint8> _color,int8 _layer):ScreenItem(_position1,_layer,_color),position2(_position2){}
    void Line::genMesh(std::vector<float> &_vertices){

    }
    UI_Container::UI_Container(vector2<int> _default_position, vector2<uint32> _default_size,vector3<uint8> _color,int8 _layer):ScreenItem(_default_position,_layer,_color),default_size(_default_size){}
    void UI_Container::genMesh(std::vector<float> &_vertices){

    }
}

namespace ScreenManager{
    void initialize(){
        textShader = initShaderFromFile("./res/shaders/textShader.vert","./res/shaders/textShader.frag","./res/shaders/textShader.geom");
        textMesh = new Mesh(nullptr,0,attrs_text_mesh);
    }
    void update(){

    }
    void setScreen(std::string _i){
        glyph_atlas = TextureBuffer::get("glyph_atlas");
        current = ScreenBuffer::get(_i);
        if(!current){
            throw EXIT_INFO("couldn't load screen: "+_i);
        }
        textMeta.clear();
        std::vector<float> textArr;
        for(ScreenItem* item : current->items){
            if(item->getType() == ScreenItemID::StaticItem){
                item->genMesh(textArr);
            }
        }
        textMesh->reload(textArr.data(),textArr.size()/7);
    }
    Screen* getCurrentScreen(){
        return current;
    }
    void draw(){
        textShader->use();
        textShader->uniformMatrix("view",Window::getView());
        glyph_atlas->use();
        for(ItemMeta itemmeta : textMeta){
            textShader->uniformMatrix("model",itemmeta.pos_mat);
            textMesh->draw(Primitive::Lines);
        };
    }
    void finalize(){

    }
}