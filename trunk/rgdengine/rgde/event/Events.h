#pragma once

namespace event
{
    class base_sender;
    class base_listener;
    class base_manager;

    // events manager base class
    class base_manager
    {
	protected:
		base_manager();
		virtual ~base_manager();

    public:
        //unsubscribe events receiver from events manager (derived from base_manager)
		virtual void unsubscribe (base_listener*) = 0;
        virtual void unsubscribe (base_listener*, base_sender*) = 0;
    };

    // events manager
    template <typename Event>
    class manager : public base_manager
    {
        //subscription info for receiving events notifications
        struct subscription
        {
            base_listener                *m_pListener; // event notification receiver
            base_sender                  *m_pSender;   //�� ���� ����� �������� ������� (0 - �� ����)
            boost::function<void(Event)>  m_func;      //����� ����� ��������

            bool operator==(const subscription &s)
            {
                return m_pListener == s.m_pListener;
            }
        };

		typedef std::list<subscription> SubscriptionsList;

    public:
        //singelton
        static manager& get()
        {
            static manager instance;
            return instance;
        }

        //��������� pListener �� ��������� ������� � ������� func �� ����������� pSender (���� ����� 0 - �� �� ����)
        void subscribe (base_listener *pListener, boost::function<void(Event)> func, base_sender *pSender)
        {
            subscription subs;
            subs.m_pListener = pListener;
            subs.m_func      = func;
            subs.m_pSender   = pSender;
            m_subscriptions.push_back(subs);
        }

		//�������� pListener �� ��������� ���� ������� ���� Event
		void unsubscribe (base_listener *listener)
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
        void unsubscribe (base_listener *listener, base_sender *sender)
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
        void send_event (const Event& event, const base_sender *pSender)
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


    // ������� ����� ����������
    class base_listener
    {
    protected:
        base_listener();
        virtual ~base_listener();

        //����������� �� ��������� �������
        template <typename Event>
        void subscribe( boost::function<void(Event)> f, base_sender *sender = 0)
        {
            manager<Event>::get().subscribe(this,f,sender);
        }

        //���������� �� ��������� �������
        template <typename Event>
        void unsubscribe(base_sender *sender)
        {
            manager<Event>::get().unsubscribe(this, sender);
        }

		template <typename Event>
		void unsubscribe()
		{
			manager<Event>::get().unsubscribe(this);
		}


    private:
        base_listener(const base_listener&);
        base_listener& operator= (const base_listener&);
    };

    // ������� ����� �����������
    class base_sender
    {
    protected:
        base_sender();
		virtual ~base_sender();

        template<typename Event>
        void base_send_event(const Event& event)
        {
			manager<Event>::get().send_event(event,this);
        }

    private:
        base_sender(const base_sender&);
        base_sender& operator= (const base_sender&);
    };

	// ����������
	class listener: private base_listener
	{
	public:
		//����������� �� ��������� �������
		//  func    - ������ � ���������� void(Event)
		//  pSender - �� ���� ����� �������� ������� (0 ��� ������, ���� ����� �������� �� ����)
		template <typename Event>
		void subscribe( boost::function<void(Event)> func, base_sender *pSender=0 )
		{
			base_listener::subscribe<Event>(func,pSender);
		}

		//����������� �� ��������� �������
		//  ptr     - ��������� �� ����-������� � ���������� void(Event)
		//  pSender - �� ���� ����� �������� ������� (0 ��� ������, ���� ����� �������� �� ����)
		template<typename Event, typename Class, typename EventArg>
		void subscribe (void (Class::*ptr)(EventArg), base_sender *pSender=0)
		{
			base_listener::subscribe<Event>( boost::bind(ptr, static_cast<Class*>(this), _1), pSender );
		}

		//���������� �� ��������� �������
		template <typename Event>
		void unsubscribe(base_sender* sender)
		{
			base_listener::unsubscribe<Event>(sender);
		}

		template <typename Event>
		void unsubscribe()
		{
			base_listener::unsubscribe<Event>();
		}
	};


	// �����������
	class sender: public listener, public base_sender
	{
	public:
		template<typename Event>
		void send_event(const Event& event)
		{
			base_send_event(event);
		}
	};
}