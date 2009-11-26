#pragma once

namespace rgde
{
	namespace core
	{
		namespace events
		{
			namespace details
			{
				class BaseSender;
				class BaseListener;
				class BaseEventsManager;

				// ������� ����� ��������� �������
				class BaseEventsManager
				{
				protected:
					BaseEventsManager();
					virtual ~BaseEventsManager();

				public:
					//�������� ���������� �� ��������� (������� ������ BaseEventsManager)
					virtual void unsubscribe (BaseListener*) = 0;
					virtual void unsubscribe (BaseListener*, BaseSender*) = 0;
				};
			}

			// ��������� ����� ��������� �������
			template <typename Event>
			class manager: public details::BaseEventsManager
			{
				//�������� �� ��������� �������
				struct Subscription
				{
					details::BaseListener                *m_pListener; //��� ����� �������� �������
					details::BaseSender                  *m_pSender;   //�� ���� ����� �������� ������� (0 - �� ����)
					boost::function<void(Event)>  m_func;      //����� ����� ��������

					bool operator==(const Subscription &s)
					{
						return m_pListener == s.m_pListener;
					}
				};

				 typedef std::list<Subscription> SubscriptionsList;

			public:
				//��������
				static manager& get()
				{
					static manager instance;
					return instance;
				}

				//��������� pListener �� ��������� ������� � ������� func �� ����������� pSender (���� ����� 0 - �� �� ����)
				void subscribe (details::BaseListener *pListener, boost::function<void(Event)> func, 
					details::BaseSender *pSender)
				{
					Subscription subs;
					subs.m_pListener = pListener;
					subs.m_func      = func;
					subs.m_pSender   = pSender;
					m_subscriptions.push_back(subs);
				}

				//�������� pListener �� ��������� ���� ������� ���� Event
				void unsubscribe (details::BaseListener *listener)
				{
					SubscriptionsList::iterator i = m_subscriptions.begin();
					while (i != m_subscriptions.end())
					{
						if (i->m_pListener == listener)
							i = m_subscriptions.erase(i);
						else
							++i;
					}
				}

				//�������� pListener �� ��������� ���� ������� ���� Event
				void unsubscribe (details::BaseListener *listener, details::BaseSender *sender)
				{
					SubscriptionsList::iterator i = m_subscriptions.begin();
					while (i != m_subscriptions.end())
					{
						if (i->m_pListener == listener && i->m_pSender == sender)
							i = m_subscriptions.erase(i);
						else
							++i;
					}
				}

				//��������� ������� event �� ����������� pSender
				void sendEvent (const Event& event, const details::BaseSender *pSender)
				{
					SubscriptionsList tmp(m_subscriptions.begin(), m_subscriptions.end());

					SubscriptionsList::iterator i = tmp.begin();
					while (i != tmp.end())
					{
						if (std::find(m_subscriptions.begin(), m_subscriptions.end(), *i) != m_subscriptions.end())
						{
							if (i->m_pSender == 0 || i->m_pSender == pSender)
								i->m_func(event);
							++i;
						}
					}
				}

			private:
				manager () {}
				~manager() {}

				manager(const manager&);
				manager& operator= (const manager&);

				SubscriptionsList m_subscriptions;
			};

			namespace details
			{
				// ������� ����� ����������
				class BaseListener
				{
				protected:
					BaseListener();
					virtual ~BaseListener();

					//����������� �� ��������� �������
					template <typename Event>
					void subscribe( boost::function<void(Event)> f, BaseSender *sender = 0)
					{
						manager<Event>::get().subscribe(this,f,sender);
					}

					//���������� �� ��������� �������
					template <typename Event>
					void unsubscribe(BaseSender *sender)
					{
						manager<Event>::get().unsubscribe(this, sender);
					}

					template <typename Event>
					void unsubscribe()
					{
						manager<Event>::get().unsubscribe(this);
					}


				private:
					BaseListener(const BaseListener&);
					BaseListener& operator= (const BaseListener&);
				};


				// ������� ����� �����������
				class BaseSender
				{
				protected:
					BaseSender();
					virtual ~BaseSender();

					template<typename Event>
					void base_send_event(const Event& event)
					{
						manager<Event>::get().sendEvent(event,this);
					}

				private:
					BaseSender(const BaseSender&);
					BaseSender& operator= (const BaseSender&);
				};
			}


			// ����������
			class listener	: private details::BaseListener
			{
			public:
				//����������� �� ��������� �������
				//  func    - ������ � ���������� void(Event)
				//  pSender - �� ���� ����� �������� ������� (0 ��� ������, ���� ����� �������� �� ����)
				template <typename Event>
				void subscribe( boost::function<void(Event)> func, details::BaseSender *pSender=0 )
				{
					details::BaseListener::subscribe<Event>(func,pSender);
				}

				//����������� �� ��������� �������
				//  ptr     - ��������� �� ����-������� � ���������� void(Event)
				//  pSender - �� ���� ����� �������� ������� (0 ��� ������, ���� ����� �������� �� ����)
				template<typename Event, typename Class, typename EventArg>
				void subscribe (void (Class::*ptr)(EventArg), details::BaseSender *pSender=0)
				{
					details::BaseListener::subscribe<Event>( 
						boost::bind(ptr, static_cast<Class*>(this), _1), pSender );
				}

				//���������� �� ��������� �������
				template <typename Event>
				void unsubscribe(details::BaseSender* sender)
				{
					details::BaseListener::unsubscribe<Event>(sender);
				}

				template <typename Event>
				void unsubscribe()
				{
					details::BaseListener::unsubscribe<Event>();
				}
			};



			// �����������
			class sender: public listener, public details::BaseSender
			{
			public:
				template<typename Event>
				void send_event(const Event& event)
				{
					base_send_event(event);
				}
			};
		}
	}
}