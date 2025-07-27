#include "screenelements.hpp"

Text::Text(vector2<int> _position, uint8 _scale, std::string _str, vector3<float> _color):position(_position),scale(_scale),str(_str),color({255.f/_color.x,255.f/_color.y,255.f/_color.z}){}