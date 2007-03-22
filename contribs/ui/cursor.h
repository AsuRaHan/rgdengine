//cursor.h
#pragma once
#include "types.h"
#include <boost/shared_ptr.hpp>

namespace ui
{

    //����������� ������
    class CCursor
    {
    public:
        CCursor (PBitmap &pBitmap, const Point &hotspot = Point(0,0));
        virtual ~CCursor ();
        
        //������� �������
        const Point& getPosition () const;
        void         setPosition (const Point &position);

        //���������
        bool isVisible  () const;
        void setVisible (bool visible);

        //���������
        virtual void render ();

    private:
        bool    m_bVisible; //������ �����/������� 
        Point   m_position; //���������� �������
        Point   m_hotspot;  //���������� "������" �������
        PBitmap m_pBitmap;  //������� �������
    };

    //������������
    typedef boost::shared_ptr<CCursor> PCursor;

} //namespace ui