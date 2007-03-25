//widget.h
#pragma once
#include "types.h"
#include <event/ecent.h>
#include <core/NamedObject.h>

namespace ui
{
    //������� ����� ��� �������
    class CWidget:
        public event::CSender,
        public core::CNamedObject
    {
    public:
        //addChild
        //removeChild
        //getChildren
        //getParent
        //setParent (protected)

        //... (���������, on***)

        virtual void update (float dt);
        virtual void render ();

    protected:
        //��������� ���� �Widget ������� ������ CSystem
        //(������ �� �� ������� � �������)
        //������� ����������� � ���������� ��������
        CWidget(std::string sName, PSystem &pSystem);
        virtual ~CWidget();

    private:
        PSystem             m_pSystem;
        std::list<CWidget*> m_children;
        //...

        CWidget (const CWidget&);
        CWidget& operator= (const CWidget&);
    };

} //namespace ui