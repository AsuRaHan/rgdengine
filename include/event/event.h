#pragma once

namespace event
{
    class CListener;
    class CActor;
    class CEvent;
    class CNamedEvent;

    //������� ����� ��� ��������� �������
    class IEventManager
    {
    public:
        IEventManager(){}
        virtual ~IEventManager(){}

        //��� ��������� ������ ����� ����������� �� �����������
        virtual void unsubscribe(CListener*)=0;

        //���! ������ ��� ��������� � ������ � ������!!! (����� ������ ������� �������)
        static void DeleteAllManagers();

        //�������� ��������� �� ���� ����������
        static void Unsubscribe(CListener*);

    protected:
        //����� ��� ���� ����� ��� ��������
		typedef std::list<IEventManager*> EventManagers;
		static EventManagers ms_listInstances;

    private:
        //�������
        IEventManager(const IEventManager&);
        IEventManager& operator=(const IEventManager&);
    };

    //��������� ����� ��� ��������� �������
    template<typename EVENT>
    class TEventManager: public IEventManager
    {
    public:
        //��� � �� ���� �������� �����
        //CActor* ����� ���� �������
        //����� CListener* �������� ��������� �� ������ CActor'�
        typedef std::pair<CListener*,CActor*> ToFrom;

        //���������� �������
        typedef std::pair<ToFrom, boost::function<void(EVENT)> > Receiver;

        //������ ����������� �������
        typedef std::list<Receiver> Receivers;

        //�������� ��������
        static TEventManager& Get();

        //�������� ����������
        void subscribe(CListener*, CActor*, boost::function<void(EVENT)>);

        //������� ����������
        void unsubscribe(CListener*);

        //������� ���������
        void sendEvent(EVENT);

    private:
        TEventManager();
        ~TEventManager();

        //�������
        TEventManager(const TEventManager&);
        TEventManager& operator=(const TEventManager&);

        //����� ��� ���� ����� ��� ��������
		static TEventManager *ms_pInstance;
		Receivers m_listReceivers;
    };

	template <typename EVENT>
	TEventManager<EVENT>* TEventManager<EVENT>::ms_pInstance = 0;

    //����������
    class CListener
    {
    public:
        CListener(){}
        virtual ~CListener();

        //�����������
        template<typename EVENT>
        void subscribe(boost::function<void(EVENT)>, CActor *pActor=0);

        //�����������
        template<typename EVENT, typename LISTENER>
        void subscribe(LISTENER*, void (LISTENER::*pFunc)(EVENT), CActor *pActor=0);

        //�������� ��� ����������� �������
        void subscribe(const std::string&, boost::function<void(const std::string&, const std::string&)>, CActor *pActor=0);

        //�������� ��� ����������� �������
        template<typename LISTENER>
        void subscribe(const std::string&, LISTENER*, void (LISTENER::*pFunc)(const std::string&, const std::string&), CActor *pActor=0);

        //����������
        template<typename EVENT>
        void unsubscribe();

        //���������� �� ������������ ������
        void unsubscribe(const std::string&);

        //���������� �� ����
        void unsubscribe();

    private:
        //�������
        CListener(const CListener&);
        CListener& operator=(const CListener&);
    };

    //���������� � �����������
    class CActor: public CListener
    {
    public:
        CActor(){}

        //������� �������
        template<typename EVENT>
        void sendEvent(EVENT);

        //������� ����������� �������
        void sendEvent(const std::string&, const std::string&);

    private:
        //�������
        CActor(const CActor&);
        CActor& operator=(const CActor&);
    };

    //������� ����� ��� �������
    class CEvent
    {
    public:
        CEvent()
			: m_pSender(0) 
		{
		}

        virtual ~CEvent() {}
        CActor* getSender() {return m_pSender;}

    protected:
        CActor* m_pSender;

    private:
        friend class CActor;
        void setSender(CActor* pSender) {m_pSender = pSender;}
    };

    //��������������� ����� ��� ������� �������
    template<class DATA>
    class TEvent: public CEvent
    {
    public:
        TEvent(const DATA &rData): m_data(rData) {}
        DATA m_data;
    };

    class CNamedEvent: public CEvent
    {
    public:
        CNamedEvent(const std::string& name, const std::string& param)
			: m_name(name), m_param(param) 
		{
		}

        std::string m_name;
        std::string m_param;
    };

    template<>
    class TEventManager<CNamedEvent>: public IEventManager
    {
    public:
        //��� � � ����� ������ �������� �������
        typedef std::pair<CListener*,std::string> To;

        //��� � �� ���� �������� �����
        //CActor* ����� ���� �������
        //����� To �������� ��������� �� ������ CActor'�
        typedef std::pair<To,CActor*> ToFrom;

        //���������� �������
        typedef std::pair<ToFrom, boost::function<void(const std::string&, const std::string&)> > Receiver;

        //������ ����������� �������
        typedef std::list<Receiver> Receivers;

        static TEventManager& Get();

        void subscribe(const std::string&, CListener*, CActor*, boost::function<void(const std::string&, const std::string&)>);

        void unsubscribe(const std::string&, CListener*);

        void unsubscribe(CListener*);

        void sendEvent(CNamedEvent);

        //��������, ��� � ����� ��������� �������� ������ ����������, �� ��� ������� � ������� �������
        bool isOtherNameSubscribe(const std::string&, CListener*);

    private:
        TEventManager();
        ~TEventManager();

        //�������
        TEventManager(const TEventManager&);
        TEventManager& operator=(const TEventManager&);

        //����� ��� ���� ����� ��� ��������
		static TEventManager *ms_pInstance;
		Receivers m_listReceivers;
    };

#include "event.inl"
}