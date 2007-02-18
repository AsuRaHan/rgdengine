//IL - Input Library
///������� ���������� ����� (�������� ����������� ��� Command)
#pragma once

#include "input/ILBase.h"

namespace input
{
  /// ������� ���������� �����
  class CControl
  {
  public:

	//���� ��������� 
    enum EType
    {
      Button, //������
      Axis,   //���
    };

    explicit CControl (EControl eName, CControl::EType eType, const CDevice &rDevice):
      m_eName   (eName),
      m_eType   (eType),
      m_rDevice (rDevice),
      m_bPress  (false),
      m_nDelta  (0),
      m_nTime   (0)
    {
    }

    virtual ~CControl ();

    //��������� ���������� � ��������
    EControl        getName   () const {return m_eName;};   //�������� enum ��������
    CControl::EType getType   () const {return m_eType;};   //�������� ��� ��������
    const CDevice&  getDevice () const {return m_rDevice;}; //�������� ����������-������ ��������

    //������ � ��������� ��������
    int  getTime  () const      {return m_nTime;}
    void setTime  (int nTime)   {m_nTime = nTime;}
    bool getPress () const      {return m_bPress;}
    void setPress (bool bPress) {m_bPress = bPress;}
    int  getDelta () const      {return m_nDelta;}
    void setDelta (int nDelta)  {m_nDelta = nDelta;}

    //Control �������� subject'�� � ������ subject-observer
    //��� observer'�� �������� ����� CCommand. ������ ��� ����
    //������:
    bool attachObserver     (CCommand*); //�������� �����������
    void detachObserver     (CCommand*); //������� �����������
    void notifyAllObservers ();          //��������� ������������ � ����� ���������

  private:
    //������ ��������
    EControl       m_eName;   //enum ��������
    EType          m_eType;   //��� ��������
    int            m_nTime;   //����� ���������� ���������� ��������
    const CDevice &m_rDevice; //����������, �������� ����������� �������

    //������ ������������ ��� ������� ��������
    std::list<CCommand*> m_listObservers;

    //������, ��������� �� ���� �������
    //(������� ��������� �������� ���� ���������� ����� ����������)
    bool m_bPress;
    int  m_nDelta;
  };
}