#pragma once
#include <lite3D/lite_utils.hpp>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

enum class ScreenItemID{
    Base,
    StaticItem,
    DynamicText,
    Rect,
    Line,
    UI_Container
};

class ScreenItem{
    public:
    vector2<int> position;
    int8 layer;
    vector3<uint8> color;
    virtual ~ScreenItem() = default;
    ScreenItem(vector2<int> _position,int8 _layer,vector3<uint8> _color);
    virtual void genMesh(std::vector<float> &_vertices);
    virtual ScreenItemID getType() const {return ScreenItemID::Base;}
};

struct ItemMeta{
    uint32 position;
    uint32 size;
    glm::mat4 pos_mat;
};

namespace ScreenItems{
    class StaticText : public ScreenItem{
        public:
        const std::string str;
        StaticText(vector2<int> _position,std::string _str, vector3<uint8> _color = {255,255,255} ,int8 _layer = 0);
        void genMesh(std::vector<float> &_vertices) override;
        ScreenItemID getType() const override {return ScreenItemID::StaticItem;}
    };  
    class DynamicText : public ScreenItem{
        public:
        std::string *str;
        DynamicText(vector2<int> _position, std::string *_str, vector3<uint8> _color = {255,255,255} ,int8 _layer = 0);
        void genMesh(std::vector<float> &_vertices) override;
        ScreenItemID getType() const override {return ScreenItemID::DynamicText;}
    };
    class Rect : public ScreenItem{
        public:
        vector2<uint32> size;
        Rect(vector2<int> _position, vector2<uint32> _size,vector3<uint8> _color = {255,255,255} ,int8 _layer = 0);
        void genMesh(std::vector<float> &_vertices) override;
        ScreenItemID getType() const override {return ScreenItemID::Rect;}
    };
    class Line : public ScreenItem{
        public:
        vector2<int> position2;
        Line(vector2<int> _position1, vector2<int> _position2,vector3<uint8> _color = {255,255,255} ,int8 _layer = 0);
        void genMesh(std::vector<float> &_vertices) override;
        ScreenItemID getType() const override {return ScreenItemID::Line;}
    };
    class UI_Container : public ScreenItem{
        public:
        vector2<uint32> default_size;
        UI_Container(vector2<int> _default_position, vector2<uint32> _default_size,vector3<uint8> _color = {255,255,255} ,int8 _layer = 0);
        void genMesh(std::vector<float> &_vertices) override;
        ScreenItemID getType() const override {return ScreenItemID::UI_Container;}
    };
}