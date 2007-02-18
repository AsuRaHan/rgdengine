#pragma once
//������� ���������� ����� �������-�������

#include "input/ILBase.h"
#include "ILSchemeImpl.h"

namespace input
{

  class CSchemeImplSimple: public ISchemeImpl
  {
  public:
    void load (std::istream &instr);  //�������� ������ �������-�������
    void save (std::ostream &outstr); //���������� ������ �������-�������
  };

}