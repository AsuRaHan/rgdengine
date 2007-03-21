//types.h
#pragma once

namespace ui
{

    class Color;
    class Size;
    class Point;
    class Rect;

    //����
    class Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    //�����
    class Size
    {
        float width;
        float height;
    };

    //�����
    class Point
    {
        float x;
        float y;
    };

    //�������������
    class Rect
    {
        float x;
        float y;
        float width;
        float height;
    };

} //namespace ui