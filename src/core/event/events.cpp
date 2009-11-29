#include "stdafx.h"

#include <rgde/core/event/events.h>

namespace rgde
{
	namespace core
	{
		namespace events
		{
			namespace
			{
				class ListManagers
				{
				public:
					ListManagers() {}
					~ListManagers() {}

					//�������� ������� ���������� ��� ���� ����������
					void unsubscribeAll (details::BaseListener *pListener);

					//�������� ��������� ���� � ����� ������ ����������
					void addManager     (details::BaseEventsManager *pManager);

					//�������� ������� ���� �� ������ ������ ����������
					void delManager     (details::BaseEventsManager *pManager);

				private:
					std::list<details::BaseEventsManager*> m_managers;
				} list_manager;
			}

			namespace details
			{

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

			}

			//�������� ������� ���������� ��� ���� ����������
			void ListManagers::unsubscribeAll(details::BaseListener *pListener)
			{
				std::list<details::BaseEventsManager*>::iterator i = m_managers.begin();
				while (i != m_managers.end())
				{
					(*i)->unsubscribe(pListener);
					++i;
				}
			}

			//�������� ��������� ���� � ����� ������ ����������
			void ListManagers::addManager (details::BaseEventsManager *pManager)
			{
				m_managers.push_back(pManager);
			}

			//�������� ������� ���� �� ������ ������ ����������
			void ListManagers::delManager (details::BaseEventsManager *pManager)
			{
				std::list<details::BaseEventsManager*>::iterator i = m_managers.begin();
				while (i != m_managers.end())
				{
					if ((*i) == pManager)
						i = m_managers.erase(i);
					else
						++i;
				}
			}

		}
	}
}