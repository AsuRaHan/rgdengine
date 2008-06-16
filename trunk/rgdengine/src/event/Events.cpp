//EventBase.cpp
#include "precompiled.h"

#include "rgde/event/Events.h"

namespace event
{
	namespace
	{
		class ListManagers
		{
		public:
			ListManagers() {}
			~ListManagers() {}

			//�������� ������� ���������� ��� ���� ����������
			void unsubscribeAll (BaseListener *pListener);

			//�������� ��������� ���� � ����� ������ ����������
			void addManager     (BaseEventsManager *pManager);

			//�������� ������� ���� �� ������ ������ ����������
			void delManager     (BaseEventsManager *pManager);

		private:
			std::list<BaseEventsManager*> m_managers;
		} list_manager;
	}


	BaseEventsManager::BaseEventsManager()
	{
		list_manager.addManager(this);
	}

	BaseEventsManager::~BaseEventsManager()
	{
		list_manager.delManager(this);
	}

	BaseListener::BaseListener() 
	{
	}

	//�������� ���������� �� ���� ����������
	BaseListener::~BaseListener()
	{		
		list_manager.unsubscribeAll(this);
	}

	BaseSender::BaseSender() 
	{
	}

	BaseSender::~BaseSender()
	{
	}

    //�������� ������� ���������� ��� ���� ����������
    void ListManagers::unsubscribeAll(BaseListener *pListener)
    {
        std::list<BaseEventsManager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            (*i)->unsubscribe(pListener);
            ++i;
        }
    }

    //�������� ��������� ���� � ����� ������ ����������
    void ListManagers::addManager (BaseEventsManager *pManager)
    {
        m_managers.push_back(pManager);
    }

    //�������� ������� ���� �� ������ ������ ����������
    void ListManagers::delManager (BaseEventsManager *pManager)
    {
        std::list<BaseEventsManager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            if ((*i) == pManager)
                i = m_managers.erase(i);
            else
                ++i;
        }
    }

}