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
			void unsubscribeAll (base_listener *listener);

			//�������� ��������� ���� � ����� ������ ����������
			void add_manager     (base_manager *manager);

			//�������� ������� ���� �� ������ ������ ����������
			void remove_manager     (base_manager *manager);

		private:
			std::list<base_manager*> m_managers;
		} list_manager;
	}


	base_manager::base_manager()
	{
		list_manager.add_manager(this);
	}

	base_manager::~base_manager()
	{
		list_manager.remove_manager(this);
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
    void ListManagers::unsubscribeAll(base_listener *listener)
    {
        std::list<base_manager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            (*i)->unsubscribe(listener);
            ++i;
        }
    }

    //�������� ��������� ���� � ����� ������ ����������
    void ListManagers::add_manager (base_manager *manager)
    {
        m_managers.push_back(manager);
    }

    //�������� ������� ���� �� ������ ������ ����������
    void ListManagers::remove_manager (base_manager *manager)
    {
        std::list<base_manager*>::iterator i = m_managers.begin();
        while (i != m_managers.end())
        {
            if ((*i) == manager)
                i = m_managers.erase(i);
            else
                ++i;
        }
    }

}