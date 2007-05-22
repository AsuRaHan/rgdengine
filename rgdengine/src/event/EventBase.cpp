//EventBase.cpp
#include "precompiled.h"

#include <rgde/event/EventBase.h>

namespace event
{
    CListManagers::CListManagers()
    {
    }

    CListManagers::~CListManagers()
    {
    }

    CListManagers& CListManagers::Get()
    {
        static CListManagers instance;
        return instance;
    }

    //�������� ������� ���������� ��� ���� ����������
    void CListManagers::unsubscribeAll(CListenerBase *pListener)
    {
        std::list<CEventManager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            (*i)->unsubscribe(pListener);
            ++i;
        }
    }

    //�������� ��������� ���� � ����� ������ ����������
    void CListManagers::addManager (CEventManager *pManager)
    {
        m_managers.push_back(pManager);
    }

    //�������� ������� ���� �� ������ ������ ����������
    void CListManagers::delManager (CEventManager *pManager)
    {
        std::list<CEventManager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            if ((*i) == pManager)
                i = m_managers.erase(i);
            else
                ++i;
        }
    }

}