//system.h
#pragma once
#include "types.h"
#include "keys.h"

namespace ui
{

    //������� ui
    class CSystem
    {
    public:
        CSystem (PRender pRender);
       ~CSystem ();

        //�������
        template <typename Widget>
        Widget* create (const std::string &sName);
        Widget* find   (const std::string &sName);
        //... (��������, �������, ������, ������)

        //�������
        void injectKey                 (keys::Keys key, bool pressed);
        void injectChar                (wchar_t ch);
        void injectMouseMove           (const Point &pos);
        void injectMouseButton         (const Point &pos, keys::MouseButtons button, bool pressed);
        void injectMouseButtonDblClick (const Point &pos, keys::MouseButtons button);

        //������
        PCursor getCursor ();
        void    setCursor (PCursor &pCursor);
        
        //���������� ��������� � ������
        void update (float dt);
        void render ();

    private:
        PRender m_pRender;
        PCursor m_pCursor;
    };

} //namespace ui