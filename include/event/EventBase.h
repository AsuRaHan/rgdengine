//EventBase.h
#pragma once
#include "base/Singelton.h"

namespace event
{

    class CSenderBase;
    class CListenerBase;

    /////////////////////////////////////
    // ������� ����� ��������� ������� //
    /////////////////////////////////////
    class CEventManager
    {
    public:
        virtual ~CEventManager(){}

        //�������� ������� ���������� ��� ���� ����������
        static void unsubscribeAll(CListenerBase *pListener)
        {
            std::list<CEventManager*>::iterator i = ms_managers.begin();
            while (i != ms_managers.end())
            {
                (*i)->unsubscribe(pListener);
                ++i;
            }
        }

    protected:
        //�������� ���������� �� ��������� (������� ������ CEventManager)
        virtual void unsubscribe (CListenerBase*) = 0;

        //�������� ��������� ���� � ����� ������ ����������
        static void addManager (CEventManager *pManager)
        {
            ms_managers.push_back(pManager);
        }

        //�������� ������� ���� �� ������ ������ ����������
        static void delManager (CEventManager *pManager)
        {
            std::list<CEventManager*>::iterator i = ms_managers.begin();
            while (i != ms_managers.end())
            {
                if ((*i) == pManager)
                    i = ms_managers.erase(i);
                else
                    ++i;
            }
        }

    private:
        static std::list<CEventManager*> ms_managers;
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

        //����������� ��������� � ���������� ������ ����������
        TEventManager ()
        {
            CEventManager::addManager(this);
        }

        //������� ����������� ���������
       ~TEventManager()
        {
            CEventManager::delManager(this);
        }

    private:
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
            CEventManager::unsubscribeAll(this);
        }

        //����������� �� ��������� �������
        template <typename Event>
        void _subscribe( boost::function<void(Event)> f, CSenderBase *pSender=0 )
        {
            base::TSingelton<TEventManager<Event> >::Get().subscribe(this,f,pSender);
        }

        //���������� �� ��������� �������
        template <typename Event>
        void _unsubscribe()
        {
            base::TSingelton<TEventManager<Event> >::Get().unsubscribe(this);
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
            base::TSingelton<TEventManager<Event> >::Get().sendEvent(event,this);
        }

    private:
        CSenderBase(const CSenderBase&);
        CSenderBase& operator= (const CSenderBase&);
    };

} //namespace event