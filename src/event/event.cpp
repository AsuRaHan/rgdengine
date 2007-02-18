//event.cpp
#include "precompiled.h"
#include "event/event.h"

namespace event
{
	IEventManager::EventManagers IEventManager::ms_listInstances;
	TEventManager<CNamedEvent> *TEventManager<CNamedEvent>::ms_pInstance= 0;

	//���! ������ ��� ��������� � ������ � ������!!! (����� ������ ������� �������)
	void IEventManager::DeleteAllManagers()
	{
		for (EventManagers::iterator i = ms_listInstances.begin(); i != ms_listInstances.end(); ++i)
		{
			IEventManager *p= *i;
			delete p;
		}
		ms_listInstances.clear();
	}

	void IEventManager::Unsubscribe(CListener *pListeber)
	{
		EventManagers::iterator i	= ms_listInstances.begin(),
								end	= ms_listInstances.end();
		while (i != end)
		{
			(*i)->unsubscribe(pListeber);
			++i;
		}
	}

	//dtor
	CListener::~CListener()
	{
		unsubscribe();
	}

	//�������� ��� ����������� �������
	void CListener::subscribe(const std::string& name, boost::function<void(const std::string&, const std::string&)> f, CActor *pActor)
	{
		//���������� � ���������
		TEventManager<CNamedEvent>::Get().subscribe(name, this, pActor, f);
	}

	//���������� �� ������������ ������
	void CListener::unsubscribe(const std::string& name)
	{
		//��������� �� ���������
		TEventManager<CNamedEvent>::Get().unsubscribe(name, this);
	}

	//���������� �� ����
	void CListener::unsubscribe()
	{
		IEventManager::Unsubscribe(this);
	}

	//������� ����������� �������
	void CActor::sendEvent(const std::string &name, const std::string &param)
	{
		sendEvent(CNamedEvent(name, param));
	}

	//�������� ��������
	TEventManager<CNamedEvent> & TEventManager<CNamedEvent>::Get()
	{
		if (0 == ms_pInstance)
			ms_pInstance = new TEventManager<CNamedEvent>();
		return *ms_pInstance;
	}

	//�������� ����������
	void TEventManager<CNamedEvent>::subscribe(const std::string& name, CListener *pListener, CActor *pActor, boost::function<void(const std::string&, const std::string&)> f)
	{
		//�������� �� ��������
		/*
			Receivers::iterator i = m_listReceivers.begin(),
				end = m_listReceivers.end();
			while (i != end)
			{
				if (boost::function_equal(i->second,f))
					return;
				++i;
			}
			*/

		//�������
		To to			= std::make_pair<CListener*, std::string>(pListener, name);
		ToFrom tofrom	= std::make_pair<To, CActor*>(to, pActor);
		Receiver rec	= std::make_pair<ToFrom, boost::function<void(const std::string&, const std::string&)> >(tofrom, f);
		m_listReceivers.push_back(rec);
	}

	//������� ����������
	void TEventManager<CNamedEvent>::unsubscribe(const std::string& name, CListener *p)
	{
		Receivers::iterator i	= m_listReceivers.begin(),
							end	= m_listReceivers.end();
		while (i != end)
			if (p == i->first.first.first) //������ �������� )
			{
				if (name == i->first.first.second)
					i = m_listReceivers.erase(i);
				else
					++i;
			}
			else
				++i;
	}

	//������� ����������
	void TEventManager<CNamedEvent>::unsubscribe(CListener *p)
	{
		Receivers::iterator i	= m_listReceivers.begin(),
							end	= m_listReceivers.end();
		while (i != end)
			if (p == i->first.first.first) //������ �������� )
				i = m_listReceivers.erase(i);
			else
				++i;
	}

	//������� ���������
	void TEventManager<CNamedEvent>::sendEvent(CNamedEvent event)
	{
		Receivers::iterator i	= m_listReceivers.begin(),
							end	= m_listReceivers.end();
		while (i != end)
		{
			if (i->first.second == 0 || i->first.second == event.getSender())
				if (i->first.first.second == event.m_name)
					i->second(event.m_name, event.m_param);
			++i;
		}
	}

	//��������, ��� � ����� ��������� �������� ������ ����������, �� ��� ������� � ������� �������
	bool TEventManager<CNamedEvent>::isOtherNameSubscribe(const std::string& name, CListener *pListener)
	{
		Receivers::iterator i	= m_listReceivers.begin(),
							end	= m_listReceivers.end();
		while (i != end)
		{
			if (i->first.first.first == pListener)
				if (i->first.first.second != name)
					return true;
			++i;
		}

		return false;
	}

	//ctor
	TEventManager<CNamedEvent>::TEventManager()
	{
		assert(!ms_pInstance);
		ms_pInstance = this;
		ms_listInstances.push_back(this);
	}

	//dtor
	TEventManager<CNamedEvent>::~TEventManager()
	{
		assert(ms_pInstance);
		ms_pInstance = 0;
		Receivers::iterator i	= m_listReceivers.begin(),
							end	= m_listReceivers.end();
		while (i != end)
			i = m_listReceivers.erase(i);
	}
} //namespace event