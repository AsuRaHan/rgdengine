//system.h
#pragma once
#include "types.h"
#include "keys.h"
#include <string>
#include <list>

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
        Widget*  create (const std::string &sName);
        CWidget* find   (const std::string &sName);
        CWidget* remove (const std::string &sName);
        CWidget* remove (const CWidget *pWidget);

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

    protected:
        std::string generateWidgetName();

    private:
        typedef std::list<CWidget*> Widgets;

        PRender m_pRender;
        PCursor m_pCursor;
        Widgets m_widgets;
    };

    //�������� �������
    template <typename Widget>
    Widget* CSystem<Widget>::create (const std::string &sName)
    {
        std::string sNewWidgetName = sName;

        //����� ������ ��� ����������
        if (find(sNewWidgetName))
            sNewWidgetName = generateNewWidgetName();

        //������� ������
        Widget *pWidget = new Widget(sNewWidgetName,*this);
        m_widgets.push_back(pWidget);
        return pWidget;
    }


} //namespace ui