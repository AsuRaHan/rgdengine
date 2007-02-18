#include "precompiled.h"

#include "input/ILCommand.h"
#include "input/ILScheme.h"
#include "input/ILSystem.h"
#include "input/ILControl.h"
#include "input/ILEvent.h"


namespace input
{

	//��������� ������� � ���������, ���������� �� CScheme
	void CCommand::attachToControl (ECommand eCommand)
	{
		std::pair<CScheme::iterator, CScheme::iterator> pairControls;
		pairControls = CScheme::GetCommandBinding(eCommand);

		for (CScheme::iterator i = pairControls.first; i!= pairControls.second; ++i)
			attachToControl (i->second.first, i->second.second); //������ �������� �� ���� ������
		//i->second.first  == EDevice
		//i->second.second == EContro
	}

	//��������� ������� � ������������� �������� ������������� ����������
	void CCommand::attachToControl (EDevice eDevice, EControl eControl)
	{
		attachToControl (CSystem::GetControl(eDevice, eControl));
	}

	//�������� ������� � ����������� ��������
	void CCommand::attachToControl (CControl *pControl)
	{
		if (pControl && !isAttachedToControl(pControl))
		{
			//���� ������� ������� ������������������ � �������
			//(�.�. ���� ��� �������� ����������), �� �������
			//������� � ������ ���������, ������� ������� �
			//������ ��������
			if (pControl->attachObserver(this))
				m_listControls.push_back(pControl);
		} 
	}

	//�������� ������� �� ������������� �������� ������������� ����������
	void CCommand::detachFromControl (EDevice eDevice, EControl eControl)
	{
		detachFromControl (CSystem::GetControl(eDevice, eControl));
	}

	//�������� ������� �� ����������� ��������
	void CCommand::detachFromControl (CControl *pControl)
	{
		std::list<CControl*>::iterator i = std::find(m_listControls.begin(), m_listControls.end(), pControl);
		if (i != m_listControls.end())
		{
			(*i)->detachObserver(this);
			m_listControls.erase(i);
		}

		//��� �������
		//... ���-�� ������ �� ��������, ����� � ������� ��� ��������
		if (m_listControls.empty())
			m_eName = InvalidCommand;
	}

	//���������, ������� �� ������� � ������������ ��������� ������������� ����������
	bool CCommand::isAttachedToControl (EDevice eDevice, EControl eControl)
	{
		return isAttachedToControl (CSystem::GetControl(eDevice, eControl));
	}

	//���������, ������� �� ������� � ���������� ���������
	bool CCommand::isAttachedToControl (CControl *pControl)
	{
		std::list<CControl*>::iterator i = std::find(m_listControls.begin(), m_listControls.end(), pControl);
		return i != m_listControls.end();
	}

	//�������� ������� �� ���� ��������
	void CCommand::detachAll ()
	{
		std::list<CControl*> listControls(m_listControls);
		m_listControls.clear();

		for (std::list<CControl*>::iterator it = listControls.begin();
			it != listControls.end(); ++it)
		{
			CControl* pControl = *it;
			pControl->detachObserver(this);
		}

		//��� �������
		//... ���-�� ������ �� ��������, ����� � ������� ��� ������
		m_eName = InvalidCommand;
	}

	//����������� CButtonCommand �� ��������� ��������� ���������� � ��� ��������
	void CButtonCommand::notify (const CControl *pControl)
	{
		assert(pControl);

		m_bPress = pControl->getPress();

		CButtonEvent event(pControl->getDevice(),*pControl,*this);
		event.m_eCommand = getName();
		event.m_nTime    = pControl->getTime();
		event.m_bPress   = m_bPress;
		event.m_eType    = m_bPress ? CEvent::Press : CEvent::Release;
		call(event);
	}

	//����������� CTriggerCommand �� ��������� ��������� ���������� � ��� ��������
	void CTriggerCommand::notify (const CControl *pControl)
	{
		assert(pControl);

		if (pControl->getPress())
		{
			m_bOn = !m_bOn;

			CTriggerEvent event(pControl->getDevice(),*pControl,*this);
			event.m_eCommand = getName();
			event.m_nTime    = pControl->getTime();
			event.m_bOn      = m_bOn;
			event.m_eType    = m_bOn ? CEvent::TriggerOn : CEvent::TriggerOff;
			call(event);
		}
	}

	//����������� CRelativeAxisCommand �� ��������� ��������� ���������� � ��� ��������
	void CRelativeAxisCommand::notify (const CControl *pControl)
	{
		assert(pControl);

		m_nDelta = pControl->getDelta();

		CRelativeAxisEvent event(pControl->getDevice(),*pControl,*this);
		event.m_eCommand = getName();
		event.m_nTime    = pControl->getTime();
		event.m_nDelta   = m_nDelta;
		event.m_eType    = CEvent::RelativeRotation;
		call(event);
	}

	//����������� CAbsoluteAxisCommand �� ��������� ��������� ���������� � ��� ��������
	void CAbsoluteAxisCommand::notify (const CControl *pControl)
	{
		assert(pControl);

		m_nCoord += pControl->getDelta();
		m_nCoord = m_nCoord<m_nMinimum ? m_nMinimum : m_nCoord>m_nMaximum ? m_nMaximum : m_nCoord;

		CAbsoluteAxisEvent event(pControl->getDevice(),*pControl,*this);
		event.m_eCommand = getName();
		event.m_nTime    = pControl->getTime();
		event.m_nCoord   = m_nCoord;
		event.m_nMinimum = m_nMinimum;
		event.m_nMaximum = m_nMaximum;
		event.m_eType    = CEvent::AbsoluteRotation;
		call(event);
	}

} //namespace input
