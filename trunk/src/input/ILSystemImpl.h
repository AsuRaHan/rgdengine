//ILSystemImpl.h

//IL - Input Library (by Dub)
//�����-������ ��� ���������� ���������� ������� �����

#ifndef _ILSystemImpl_
#define _ILSystemImpl_

#include "input/ILBase.h"
#include <map>

namespace input
{

  //////////////////////////////////////////////////////////
  // �����-������ ��� ���������� ���������� ������� ����� //
  //////////////////////////////////////////////////////////
  class ISystemImpl
  {
  public:
    ISystemImpl () {}
    virtual ~ISystemImpl ();

    //������ � ����������� �����
    CDevice* getDevice       (EDevice); //�������� ����������
    bool     isDevicePresent (EDevice); //���������, ���������� �� ��������� ����������

    //������ � ���������
    CControl* getControl       (EDevice, EControl); //�������� �������
    bool      isControlPresent (EDevice, EControl); //���������, ���������� �� ���������� �������

    //������ ������� ����� (��������� ���������� ��
    //��������� ����� � �������� �� �� ���������)
    virtual void update () = 0;

  protected:
    //������ ���� ����� ����� ������� ����� ������ ���������� �����
    //���� ����� ����� ������������ ������ ������� ISystemImpl
    CDevice* newDevice (EDevice);

    //������ ���� ����� ����� �������� ������ � ���������� �����
    //���� ����� ����� ������������ ������ ������� ISystemImpl
    void addControl (EDevice, CControl*);

  private:
    //����� ���������
    std::map<EDevice,CDevice*> m_mapDevices;

    //������ ������������ ����������� � ��������� ������������
    ISystemImpl (const ISystemImpl&);
    ISystemImpl& operator= (const ISystemImpl&);
  };

} //namespace input

#endif //_ILSystemImpl_


