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
			void unsubscribeAll (base_listener *pListener);

			//�������� ��������� ���� � ����� ������ ����������
			void addManager     (base_manager *pManager);

			//�������� ������� ���� �� ������ ������ ����������
			void delManager     (base_manager *pManager);

		private:
			std::list<base_manager*> m_managers;
		} list_manager;
	}


	base_manager::base_manager()
	{
		list_manager.addManager(this);
	}

	base_manager::~base_manager()
	{
		list_manager.delManager(this);
	}

	base_listener::base_listener() 
	{
	}

	//�������� ���������� �� ���� ����������
	base_listener::~base_listener()
	{		
		list_manager.unsubscribeAll(this);
	}

	base_sender::base_sender() 
	{
	}

	base_sender::~base_sender()
	{
	}

    //�������� ������� ���������� ��� ���� ����������
    void ListManagers::unsubscribeAll(base_listener *pListener)
    {
        std::list<base_manager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            (*i)->unsubscribe(pListener);
            ++i;
        }
    }

    //�������� ��������� ���� � ����� ������ ����������
    void ListManagers::addManager (base_manager *pManager)
    {
        m_managers.push_back(pManager);
    }

    //�������� ������� ���� �� ������ ������ ����������
    void ListManagers::delManager (base_manager *pManager)
    {
        std::list<base_manager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            if ((*i) == pManager)
                i = m_managers.erase(i);
            else
                ++i;
        }
    }

}