#pragma once

#include "input/ILBase.h"

namespace input
{
  ///////////////////////////
  // ������� ������� ����� //
  ///////////////////////////
  class CEvent
  {
  public:
    //���� ������� �����
    enum EType
    {
      Press            =  1, //�������
      Release          =  2, //�������
      TriggerOn        =  4, //������� �������
      TriggerOff       =  8, //������� ��������
      RelativeRotation = 16, //������������ ��������� ���������� ��� (������)
      AbsoluteRotation = 32, //���������� ��������� ���������� ��� (����������)

      All              = 63, //����� ��� ���� ����� �������
      InvalidEvent     = 64, //��� ������� - ����� ������� ���� �� ������
    };

    explicit CEvent (const CDevice &rDevice, const CControl &rControl):
      m_rDevice  (rDevice),
      m_rControl (rControl),
      m_eCommand (InvalidCommand),
      m_eType    (InvalidEvent)
    {
    }

    //����� ������ ��� ������ ���� ������� �����
    const CDevice  &m_rDevice;  //����������, �� �������� ������ �������
    const CControl &m_rControl; //�������, �� �������� ������ �������
    ECommand        m_eCommand; //��� �������, ��� ������� ������������ ������ �����
    EType           m_eType;    //��� �������
    int             m_nTime;    //����� ��������� �������
  };

  ///////////////////////////////////////////////
  // �������, ������������� ��� CButtonCommand //
  ///////////////////////////////////////////////
  class CButtonEvent: public CEvent
  {
  public:
    explicit CButtonEvent
    (
      const CDevice        &rDevice,
      const CControl       &rControl,
      const CButtonCommand &rCommand
    ):
      CEvent     (rDevice,rControl),
      m_rCommand (rCommand),
      m_bPress   (false)
    {
    }

    //������ ��� ������
    const CButtonCommand &m_rCommand; //������ �� ������� ��� ������
    bool m_bPress;                    //��������� ������
  };

  ////////////////////////////////////////////////
  // �������, ������������� ��� CTriggerCommand //
  ////////////////////////////////////////////////
  class CTriggerEvent: public CEvent
  {
  public:
    explicit CTriggerEvent
    (
      const CDevice         &rDevice,
      const CControl        &rControl,
      const CTriggerCommand &rCommand
    ):
      CEvent     (rDevice,rControl),
      m_rCommand (rCommand),
      m_bOn      (false)
    {
    }

    //������ ��� ��������
    const CTriggerCommand &m_rCommand; //������ �� ������� ��� ��������
    bool m_bOn;                        //��������� ��������
  };

  /////////////////////////////////////////////////////
  // �������, ������������� ��� CRelativeAxisCommand //
  /////////////////////////////////////////////////////
  class CRelativeAxisEvent: public CEvent
  {
  public:
    explicit CRelativeAxisEvent
    (
      const CDevice              &rDevice,
      const CControl             &rControl,
      const CRelativeAxisCommand &rCommand
    ):
      CEvent     (rDevice,rControl),
      m_rCommand (rCommand),
      m_nDelta   (0)
    {
    }

    //������ ��� �������������� �������� ���
    const CRelativeAxisCommand &m_rCommand; //������ �� ������� ��� �������������� �������� ���
    int m_nDelta;                           //����� ���
  };

  //////////////////////////////////////////////////////
  // �������, ������������� ��� CAbsoluteAxisCommands //
  //////////////////////////////////////////////////////
  class CAbsoluteAxisEvent: public CEvent
  {
  public:
    explicit CAbsoluteAxisEvent
    (
      const CDevice              &rDevice,
      const CControl             &rControl,
      const CAbsoluteAxisCommand &rCommand
    ):
      CEvent     (rDevice,rControl),
      m_rCommand (rCommand),
      m_nCoord   (0),
      m_nMinimum (0),
      m_nMaximum (0)
    {
    }

    //������ ��� ����������� �������� ���
    const CAbsoluteAxisCommand &m_rCommand; //������ �� ������� ��� ����������� �������� ���
    int m_nCoord;                           //���������� ���
    int m_nMinimum;                         //����������� �������� ��� ���
    int m_nMaximum;                         //������������ �������� ��� ���
  };
}