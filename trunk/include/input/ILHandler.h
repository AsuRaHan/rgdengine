//ILHandler.h

//IL - Input Library (by Dub)
//������� ��� �������� ������� ��������� ������� � �������

#ifndef _ILHandler_
#define _ILHandler_

#include "input/ILBase.h"
#include <cassert>

namespace input
{

  ////////////////////////////////////////
  // ������� ��������� ��� ������������ //
  ////////////////////////////////////////
  class IHandler
  {
  public:
    IHandler () {}
    virtual ~IHandler() {}

    virtual void call (const CEvent             &rArg) = 0;
    virtual void call (const CButtonEvent       &rArg) = 0;
    virtual void call (const CTriggerEvent      &rArg) = 0;
    virtual void call (const CRelativeAxisEvent &rArg) = 0;
    virtual void call (const CAbsoluteAxisEvent &rArg) = 0;

  private:
    IHandler (const IHandler&);
    IHandler& operator= (const IHandler&);
  };

  ///////////////////////////////////////////
  // ���������� ��� ������ ������� ������� //
  ///////////////////////////////////////////
  template <typename RECEIVER, typename ARG>
  struct TMethodHandler: public IHandler
  {
    typedef void (RECEIVER::*ACTION)(const ARG&);

    //�����������
    TMethodHandler
    (
      RECEIVER *pPeceiver,
      ACTION    pAction
    ):
      m_pReceiver (pReceiver),
      m_pAction   (pAction)
    {
    }

    //����������
    virtual ~TMethodHandler () {}

  private:
    RECEIVER *pReceiver;
    ACTION    pAtion;

    TMethodHandler (const TMethodHandler&);
    TMethodHandler& operator= (const TMethodHandler&);
  };

  //////////////////////////////////////////////////////////////
  // ������������� TMethodHandler ��� ������ ����� ���������� //
  //////////////////////////////////////////////////////////////

  //������������� ��� CEvent
  template <typename RECEIVER>
  struct TMethodHandler<RECEIVER,CEvent>: public IHandler
  {
    typedef void (RECEIVER::*ACTION)(const CEvent&);

    //�����������
    TMethodHandler
    (
      RECEIVER *pReceiver,
      ACTION    pAction
    ):
      m_pReceiver (pReceiver),
      m_pAction   (pAction)
    {
    }

    //����������
    virtual ~TMethodHandler () {}

    //�����
    void call (const CEvent             &rArg) {(m_pReceiver->*m_pAction)(        rArg);}
    void call (const CButtonEvent       &rArg) {(m_pReceiver->*m_pAction)((CEvent)rArg);}
    void call (const CTriggerEvent      &rArg) {(m_pReceiver->*m_pAction)((CEvent)rArg);}
    void call (const CRelativeAxisEvent &rArg) {(m_pReceiver->*m_pAction)((CEvent)rArg);}
    void call (const CAbsoluteAxisEvent &rArg) {(m_pReceiver->*m_pAction)((CEvent)rArg);}

  private:
    RECEIVER *m_pReceiver;
    ACTION    m_pAction;

    TMethodHandler (const TMethodHandler&);
    TMethodHandler& operator= (const TMethodHandler&);
  };

  //������������� ��� CButtonEvent
  template <typename RECEIVER>
  struct TMethodHandler<RECEIVER,CButtonEvent>: public IHandler
  {
    typedef void (RECEIVER::*ACTION)(const CButtonEvent&);

    //�����������
    TMethodHandler
    (
      RECEIVER *pReceiver,
      ACTION    pAction
    ):
      m_pReceiver (pReceiver),
      m_pAction   (pAction)
    {
    }

    //����������
    virtual ~TMethodHandler () {}

    //�����
    void call (const CEvent             &rArg) {}
    void call (const CButtonEvent       &rArg) {(m_pReceiver->*m_pAction)(rArg);}
    void call (const CTriggerEvent      &rArg) {}
    void call (const CRelativeAxisEvent &rArg) {}
    void call (const CAbsoluteAxisEvent &rArg) {}

  private:
    RECEIVER *m_pReceiver;
    ACTION    m_pAction;

    TMethodHandler (const TMethodHandler&);
    TMethodHandler& operator= (const TMethodHandler&);
  };

  //������������� ��� CTriggerEvent
  template <typename RECEIVER>
  struct TMethodHandler<RECEIVER,CTriggerEvent>: public IHandler
  {
    typedef void (RECEIVER::*ACTION)(const CTriggerEvent&);

    //�����������
    TMethodHandler
    (
      RECEIVER *pReceiver,
      ACTION    pAction
    ):
      m_pReceiver (pReceiver),
      m_pAction  (pAction)
    {
    }

    //����������
    virtual ~TMethodHandler () {}

    //�����
    void call (const CEvent             &rArg) {}
    void call (const CButtonEvent       &rArg) {}
    void call (const CTriggerEvent      &rArg) {(m_pReceiver->*m_pAction)(rArg);}
    void call (const CRelativeAxisEvent &rArg) {}
    void call (const CAbsoluteAxisEvent &rArg) {}

  private:
    RECEIVER *m_pReceiver;
    ACTION    m_pAction;

    TMethodHandler (const TMethodHandler&);
    TMethodHandler& operator= (const TMethodHandler&);
  };

  //������������� ��� CRelativeAxisEvent
  template <typename RECEIVER>
  struct TMethodHandler<RECEIVER,CRelativeAxisEvent>: public IHandler
  {
    typedef void (RECEIVER::*ACTION)(const CRelativeAxisEvent&);

    //�����������
    TMethodHandler
    (
      RECEIVER *pReceiver,
      ACTION    pAction
    ):
      m_pReceiver (pReceiver),
      m_pAction   (pAction)
    {
    }

    //����������
    virtual ~TMethodHandler () {}

    //�����
    void call (const CEvent             &rArg) {}
    void call (const CButtonEvent       &rArg) {}
    void call (const CTriggerEvent      &rArg) {}
    void call (const CRelativeAxisEvent &rArg) {(m_pReceiver->*m_pAction)(rArg);}
    void call (const CAbsoluteAxisEvent &rArg) {}

  private:
    RECEIVER *m_pReceiver;
    ACTION    m_pAction;

    TMethodHandler (const TMethodHandler&);
    TMethodHandler& operator= (const TMethodHandler&);
  };

  //������������� ��� CAbsoluteAxisEvent
  template <typename RECEIVER>
  struct TMethodHandler<RECEIVER,CAbsoluteAxisEvent>: public IHandler
  {
    typedef void (RECEIVER::*ACTION)(const CAbsoluteAxisEvent&);

    //�����������
    TMethodHandler
    (
      RECEIVER *pReceiver,
      ACTION    pAction
    ):
      m_pReceiver (pReceiver),
      m_pAction   (pAction)
    {
    }

    //����������
    virtual ~TMethodHandler () {}

    //�����
    void call (const CEvent             &rArg) {}
    void call (const CButtonEvent       &rArg) {}
    void call (const CTriggerEvent      &rArg) {}
    void call (const CRelativeAxisEvent &rArg) {}
    void call (const CAbsoluteAxisEvent &rArg) {(m_pReceiver->*m_pAction)(rArg);}

  private:
    RECEIVER *m_pReceiver;
    ACTION    m_pAction;

    TMethodHandler (const TMethodHandler&);
    TMethodHandler& operator= (const TMethodHandler&);
  };

} //namespace input

#endif //_ILHandler_