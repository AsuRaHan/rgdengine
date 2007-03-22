//types.h
#pragma once
#include <boost/shared_ptr.hpp>

namespace ui
{
    //���������������
    class  CSystem;
    class  CCursor;
    struct IRender;
    struct IBitmap;
    struct IFont;

    //�������������
    typedef boost::shared_ptr<CSystem> PSystem;
    typedef boost::shared_ptr<CCursor> PCursor;
    typedef boost::shared_ptr<IRender> PRender;
    typedef boost::shared_ptr<IBitmap> PBitmap;
    typedef boost::shared_ptr<IFont  > PFont;

    //��������������� ����
    struct Color;
    struct Rect;
    struct Size;
    struct Point;
    //...

} //namespace ui