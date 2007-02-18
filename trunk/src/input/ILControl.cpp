#include "precompiled.h"

#include "input/ILControl.h"
#include "input/ILCommand.h"

namespace input
{

  CControl::~CControl ()
  {
	  // ������� ����� ������
	  std::list<CCommand*> listObservers(m_listObservers);

	  // �������� ������ ������
	  m_listObservers.clear();

	  // �������� ���� ����������
	  for (std::list<CCommand*>::iterator it = listObservers.begin();
		  it != listObservers.end(); ++it)
	  {
		  CCommand* pObserver = *it;
		  pObserver->detachFromControl(this);
	  }
  }

  //�������� �����������
  bool CControl::attachObserver (CCommand *pCommand)
  {
    //�������� �� ������������� ������� � ��������
    if
    (
      (
        m_eType == CControl::EType::Axis &&
        (
          pCommand->getType() == CCommand::EType::Trigger ||
          pCommand->getType() == CCommand::EType::Button
        )
      )
      ||
      (
        m_eType == CControl::EType::Button &&
        (
          pCommand->getType() == CCommand::EType::AbsoluteAxis ||
          pCommand->getType() == CCommand::EType::RelativeAxis
        )
      )
    )
    {
      //... �������� � ������������ ����� �������� � �������
      return false;
    }

    m_listObservers.push_back(pCommand);
    return true;
  }

  //������� �����������
  void CControl::detachObserver (CCommand *pCommand)
  {
    std::list<CCommand*>::iterator i = std::find
    (
      m_listObservers.begin(),
      m_listObservers.end(),
      pCommand
    );

    if (i == m_listObservers.end())
    {
      //... �������� �� ���������� ������� � ������ ������������
      return;
    }

    m_listObservers.erase(i);
  }

  //��������� ������������ � ����� ���������
  void CControl::notifyAllObservers ()
  {
//->
    //�� ����� ����������� �� �������� ������� �������� ����� ���������
    //��������� ������ ���������� -> ������ ���������� ����� ����������,
    //� ������ ��������� ����� ����� �����������. ������������ � ������
    //�����.
    std::list<CCommand*> listTempObservers(m_listObservers);
    std::list<CCommand*>::iterator i   = listTempObservers.begin(),
                                   end = listTempObservers.end();
    for(; i != end; ++i)
      if
      (
        std::find
        (
          m_listObservers.begin(),
          m_listObservers.end(),
          *i
        ) !=
        m_listObservers.end()
      )
        (*i)->notify(this);
/*
    std::list<CCommand*>::iterator i   = m_listObservers.begin(),
                                   end = m_listObservers.end();
    for(; i!=end; ++i)
      (*i)->notify(this);
*/
//-<
  }

} //namespace input
