//Event.h
#pragma once
#include "EventBase.h"

namespace event
{

    ////////////////
    // ���������� //
    ////////////////
    class CListener: private CListenerBase
    {
    public:
        //����������� �� ��������� �������
        //  func    - ������ � ���������� void(Event)
        //  pSender - �� ���� ����� �������� ������� (0 ��� ������, ���� ����� �������� �� ����)
        template <typename Event>
        void subscribe( boost::function<void(Event)> func, CSenderBase *pSender=0 )
        {
            _subscribe<Event>(func,pSender);
        }

        //����������� �� ��������� �������
        //  ptr     - ��������� �� ����-������� � ���������� void(Event)
        //  pSender - �� ���� ����� �������� ������� (0 ��� ������, ���� ����� �������� �� ����)
        template<typename Event, typename Class, typename EventArg>
        void subscribe (void (Class::*ptr)(EventArg), CSenderBase *pSender=0)
        {
            _subscribe<Event>( boost::bind(ptr, static_cast<Class*>(this), _1), pSender );
        }

        //���������� �� ��������� �������
        template <typename Event>
        void unsubscribe()
        {
            _unsubscribe<Event>();
        }
    };

    /////////////////
    // ����������� //
    /////////////////
    class CSender: public CListener, public CSenderBase
    {
    public:
        //��������� �������
        template<typename Event>
        void sendEvent(Event event)
        {
            _sendEvent<Event>(event);
        }
    };

} //namespace event