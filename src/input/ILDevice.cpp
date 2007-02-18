#include "precompiled.h"

#include "input/ILDevice.h"
#include "input/ILControl.h"

namespace input
{

  CDevice::~CDevice ()
  {
    while (!m_mapControls.empty())
    {
      delete m_mapControls.begin()->second;
      m_mapControls.erase(m_mapControls.begin());
    }
  }

  //�������� �������
  CControl* CDevice::getControl (EControl eControl)
  {
    std::map<EControl,CControl*>::const_iterator pos = m_mapControls.find(eControl);

    if (pos == m_mapControls.end())
      return 0;

    return pos->second;
  }

  //���� �� ����� �������
  bool CDevice::isControlPresent (EControl eControl)
  {
    return m_mapControls.find(eControl) != m_mapControls.end();
  }

} //namespace input