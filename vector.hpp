#pragma once

template<typename T>
struct vector2{
    T x;
    T y;
    vector2(T _x,T _y):x(_x),y(_y){}
};

template<typename T>
struct vector3{
    T x;
    T y;
    T z;
    vector3(T _x,T _y,T _z):x(_x),y(_y),z(_z){}
};