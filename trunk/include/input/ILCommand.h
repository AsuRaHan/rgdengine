//ILCommand.h

//IL - Input Library (by Dub)
//������� ��� ������� ����� (�������� ������������ ��� CControl)

#ifndef _ILCommand_
#define _ILCommand_

#include "input/ILBase.h"
#include "input/ILHandler.h"
#include "input/ILCommandEnum.h"
#include <list>

namespace input
{

  ///////////////////////////
  // ������� ����� ������� //
  ///////////////////////////
  class CCommand
  {
  public:
    //���� ������
    enum EType
    {
      Button,       //������
      Trigger,      //�������
      RelativeAxis, //������������� ��������� ��� (������)
      AbsoluteAxis, //���������� ��������� ��� (����������)
    };

    //����������
    virtual ~CCommand ()
    {
      while (!m_listHandlers.empty())
      {
        delete *m_listHandlers.begin();
        m_listHandlers.erase(m_listHandlers.begin());
      }
      detachAll();
    }

    //��������� ���������� � �������
    ECommand        getName () const {return m_eName;}; //�������� enum �������
    CCommand::EType getType () const {return m_eType;}; //�������� ��� �������

    //������ �� ������� �������-��������
    void attachToControl (ECommand);
    void attachToControl (EDevice, EControl);
    void attachToControl (CControl*);

    void detachFromControl (EDevice, EControl);
    void detachFromControl (CControl*);

    bool isAttachedToControl (EDevice, EControl);
    bool isAttachedToControl (CControl*);

    void detachAll ();

    //������� ��������� ���� ���������
    template <typename ARG>
    void call (const ARG &rArg)
    {
      std::list<IHandler*>::const_iterator i = m_listHandlers.begin(),
        end = m_listHandlers.end();
      while (i!=end)
      {
        (*i)->call(rArg);
        ++i;
      }
    }

    //����� Command �������� ������������ ������ Control
    //����� Notify ���������� ��� ��������� ��������� Control
    virtual void notify (const CControl*) = 0;

  protected:
    //�������� ����������
    void pushHandler(IHandler *pHandler) {m_listHandlers.push_back(pHandler);}

    //���������� ����������� (��������� ����� ������ �������� ������ Command)
    explicit CCommand (EType eType):
      m_eType (eType),
      m_eName (InvalidCommand)
    {
    }

  private:
    //������ ��� �������
    ECommand             m_eName;        //enum �������
    std::list<CControl*> m_listControls; //��������, � ������� ��������� �������
    EType                m_eType;        //��� �������

    //������ �����������
    std::list<IHandler*> m_listHandlers;

    //������ �������� �����
    CCommand (const CCommand&);
    CCommand& operator= (const CCommand&);
  };

  ////////////////////
  // ������� ������ //
  ////////////////////
  class CButtonCommand: public CCommand
  {
  public:
    //����������
    CButtonCommand(): CCommand(CCommand::Button), m_bPress(false) {}

    //�������� ����������� ��� �������
    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CEvent>(pReciver,pAction));
    }

    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CButtonEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CButtonEvent>(pReciver,pAction));
    }

    //����� Command �������� ������������ ������ CControl
    //����� Notify ���������� ��� ��������� ��������� CControl
    void notify(const CControl*);

    //����� ��������� �������
    operator bool () const {return m_bPress;}

  private:
    bool m_bPress; //������ �� ������
  };

  ///////////////////////////
  // ������� ������������� //
  ///////////////////////////
  class CTriggerCommand: public CCommand
  {
  public:
    //����������
    CTriggerCommand(): CCommand(CCommand::Trigger), m_bOn(false) {}

    //�������� ����������� ��� �������
    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CEvent>(pReciver,pAction));
    }

    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CTriggerEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CTriggerEvent>(pReciver,pAction));
    }

    //����� Command �������� ������������ ������ Control
    //����� Notify ���������� ��� ��������� ��������� Control
    void notify(const CControl*);

    //����� ��������� �������
    operator bool () const {return m_bOn;}

    //������� ��������� ��������
    void setState (bool on) {m_bOn = on;}

  private:
    bool m_bOn; //������ �� �������
  };

  ///////////////////////////////
  // ������� ������������� ��� //
  ///////////////////////////////
  class CRelativeAxisCommand: public CCommand
  {
  public:
    //����������
    CRelativeAxisCommand(): CCommand(CCommand::RelativeAxis), m_nDelta(0) {}

    //�������� ����������� ��� �������
    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CEvent>(pReciver,pAction));
    }

    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CRelativeAxisEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CRelativeAxisEvent>(pReciver,pAction));
    }

    //����� Command �������� ������������ ������ Control
    //����� Notify ���������� ��� ��������� ��������� Control
    void notify(const CControl*);

    //����� ��������� �������
    operator int () const {return m_nDelta;}
    int getDelta () const {return m_nDelta;}

  private:
    int m_nDelta; //��������� ����� ������������� ���
  };

  ////////////////////////////
  // ������� ���������� ��� //
  ////////////////////////////
  class CAbsoluteAxisCommand: public CCommand
  {
  public:
    //����������
    CAbsoluteAxisCommand(): CCommand(CCommand::AbsoluteAxis), m_nCoord(50), m_nMinimum(0), m_nMaximum(100) {}

    //�������� ����������� ��� �������
    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CEvent>(pReciver,pAction));
    }

    template <typename RECIVER>
    void addHandler (RECIVER *pReciver, void (RECIVER::*pAction)(const CAbsoluteAxisEvent&))
    {
      pushHandler(new TMethodHandler<RECIVER,CAbsoluteAxisEvent>(pReciver,pAction));
    }

    //����� Command �������� ������������ ������ Control
    //����� Notify ���������� ��� ��������� ��������� Control
    void notify(const CControl*);

    //����� ��������� �������
    operator int   () const {return m_nCoord;}
    int getCoord   () const {return m_nCoord;}
    int getMinimum () const {return m_nMinimum;}
    int getMaximum () const {return m_nMaximum;}

    //��������� ���������� ���
    void setState (int minimum, int maximum, int coord)
    {
      m_nMinimum = minimum < maximum ? minimum : maximum;
      m_nMaximum = minimum < maximum ? maximum : minimum;
      m_nCoord   = coord < m_nMinimum ? m_nMinimum : coord > m_nMaximum ? m_nMaximum : coord;
    }

  private:
    int m_nCoord;   //���������� ���������� ���
    int m_nMinimum; //����������� �������� ���������� ��� ���������� ���
    int m_nMaximum; //������������ �������� ���������� ��� ���������� ���
  };

} //namespace input

#endif //_ILCommand_