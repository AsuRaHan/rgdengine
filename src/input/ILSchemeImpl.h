//ILSchemeImpl.h

//IL - Input Library (by Dub)
//�����-������ ������������� ��� ��������� ������ "�������-�������"

#ifndef _ILSchemeImpl_
#define _ILSchemeImpl_

#include "input/ILBase.h"
#include <iostream>

namespace input
{

  ///////////////////////////////////////////////////////////////////////
  // �����-������ ������������� ��� ��������� ������ "�������-�������" //
  ///////////////////////////////////////////////////////////////////////
  class ISchemeImpl
  {
  public:
    virtual ~ISchemeImpl() {}

    virtual void load (std::istream &instr)  = 0; //�������� ������ �������-�������
    virtual void save (std::ostream &outstr) = 0; //���������� ������ �������-�������
  };

} //namespace input

#endif //_ILSchemeImpl_