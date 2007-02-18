#include "precompiled.h"

#include "input/ILSystem.h"
#include "input/ILSystemImpl.h"


namespace input
{

  //��������� �� ������������ ���������
  //�� ��������� � ��� ����, �� ��� ����� ��������� �� ���� :)
  CSystem* CSystem::ms_pInstance = 0;

  //������ ��� ��������������� ���������
  CSystem::CSystem ()
  {
    assert(!ms_pInstance);
    ms_pInstance = this;
  }

  CSystem::~CSystem ()
  {
    assert(ms_pInstance);
    ms_pInstance = 0;
  }

  //�������� ��������� �� �������� ������� �����
  CSystem& CSystem::Get ()
  {
    if (!ms_pInstance)
      ms_pInstance = new CSystem;
    return *ms_pInstance;
  }

  //������� �������� ������� �����
  void CSystem::Destroy ()
  {
    if (ms_pInstance)
      delete ms_pInstance;
    ms_pInstance = 0;
  }

  //���������������� ������� �����
  void CSystem::init (ISystemImpl *pImpl)
  {
    m_pImpl.reset(pImpl);
  }

  //�������� ����������
  CDevice* CSystem::GetDevice (EDevice eDevice)
  {
    return Get().m_pImpl->getDevice(eDevice);
  }

  //���������, ���������� �� ��������� ����������
  bool CSystem::IsDevicePresent (EDevice eDevice)
  {
    return Get().m_pImpl->isDevicePresent(eDevice);
  }

  //�������� �������
  CControl* CSystem::GetControl (EDevice eDevice, EControl eControl)
  {
    return Get().m_pImpl->getControl(eDevice,eControl);
  }

  //���������, ���������� �� ���������� �������
  bool CSystem::IsControlPresent (EDevice eDevice, EControl eControl)
  {
    return Get().m_pImpl->isControlPresent(eDevice,eControl);
  }

  //������� �� ������ ��� ������� �� ��������� �����
  void CSystem::Update ()
  {
    Get().m_pImpl->update();
  }

} //namespace input
