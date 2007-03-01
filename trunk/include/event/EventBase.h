//EventBase.h
#pragma once
#include "base/Singelton.h"

namespace event
{

    class CSenderBase;
    class CListenerBase;
    class CEventManager;

    /////////////////////////////////////////
    // �������� �� ������� ���� ���������� //
    /////////////////////////////////////////
    class CListManagers
    {
    public:
        static CListManagers& Get();
        void unsubscribeAll (CListenerBase *pListener); //�������� ������� ���������� ��� ���� ����������
        void addManager     (CEventManager *pManager);  //�������� ��������� ���� � ����� ������ ����������
        void delManager     (CEventManager *pManager);  //�������� ������� ���� �� ������ ������ ����������

    private:
        CListManagers();
       ~CListManagers();

        std::list<CEventManager*> m_managers;
    };

    /////////////////////////////////////
    // ������� ����� ��������� ������� //
    /////////////////////////////////////
    class CEventManager
    {
    public:
        virtual ~CEventManager(){}

        //�������� ���������� �� ��������� (������� ������ CEventManager)
        virtual void unsubscribe (CListenerBase*) = 0;
    };

    ///////////////////////////////////////
    // ��������� ����� ��������� ������� //
    ///////////////////////////////////////
    template <typename Event>
    class TEventManager: public CEventManager
    {
        //�������� �� ��������� �������
        struct Subscription
        {
            CListenerBase                *m_pListener; //��� ����� �������� �������
            CSenderBase                  *m_pSender;   //�� ���� ����� �������� ������� (0 - �� ����)
            boost::function<void(Event)>  m_func;      //����� ����� ��������

            bool operator==(const Subscription &s)
            {
                //->
                //return
                //(
                //    m_pListener == s.m_pListener &&    
                //    m_pSender   == s.m_pSender   &&
                //    m_func      == s.m_func
                //);
                return m_pListener == s.m_pListener;
                //-<
            }
        };

    public:
        //�������� ���
        static TEventManager& Get()
        {
            static TEventManager instance;
            return instance;
        }

        //��������� pListener �� ��������� ������� � ������� func �� ����������� pSender (���� ����� 0 - �� �� ����)
        void subscribe (CListenerBase *pListener, boost::function<void(Event)> func, CSenderBase *pSender)
        {
            Subscription subs;
            subs.m_pListener = pListener;
            subs.m_func      = func;
            subs.m_pSender   = pSender;
            m_subscriptions.push_back(subs);
        }

        //�������� pListener �� ��������� ���� ������� ���� Event
        void unsubscribe (CListenerBase *pListener)
        {
            std::list<Subscription>::iterator i = m_subscriptions.begin();
            while (i != m_subscriptions.end())
            {
                if (i->m_pListener == pListener)
                    i = m_subscriptions.erase(i);
                else
                    ++i;
            }
        }

        //��������� ������� event �� ����������� pSender
        void sendEvent (Event event, const CSenderBase *pSender)
        {
            std::list<Subscription> tmp(m_subscriptions.begin(), m_subscriptions.end());

            std::list<Subscription>::iterator i = tmp.begin();
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
        //����������� ��������� � ���������� ������ ����������
        TEventManager ()
        {
            CListManagers::Get().addManager(this);
        }

        //������� ����������� ���������
       ~TEventManager()
        {
            CListManagers::Get().delManager(this);
        }

        TEventManager(const TEventManager&);
        TEventManager& operator= (const TEventManager&);

        std::list<Subscription> m_subscriptions;
    };    

    //////////////////////////////
    // ������� ����� ���������� //
    //////////////////////////////
    class CListenerBase
    {
    protected:
        CListenerBase() {}

        //�������� ���������� �� ���� ����������
        virtual ~CListenerBase()
        {
            CListManagers::Get().unsubscribeAll(this);
        }

        //����������� �� ��������� �������
        template <typename Event>
        void _subscribe( boost::function<void(Event)> f, CSenderBase *pSender=0 )
        {
            TEventManager<Event>::Get().subscribe(this,f,pSender);
        }

        //���������� �� ��������� �������
        template <typename Event>
        void _unsubscribe()
        {
            TEventManager<Event>::Get().unsubscribe(this);
        }

    private:
        CListenerBase(const CListenerBase&);
        CListenerBase& operator= (const CListenerBase&);
    };

    ///////////////////////////////
    // ������� ����� ����������� //
    ///////////////////////////////
    class CSenderBase
    {
    protected:
        CSenderBase() {}

        //��������� �������
        template<typename Event>
        void _sendEvent(Event event)
        {
            TEventManager<Event>::Get().sendEvent(event,this);
        }

    private:
        CSenderBase(const CSenderBase&);
        CSenderBase& operator= (const CSenderBase&);
    };

} //namespace event