#pragma once

#include "input/ILBase.h"

namespace input
{
  /////////////////////////////////////////////////////////////
  // ����� "����� ������� ������������ ������������ �������" //
  /////////////////////////////////////////////////////////////
  class CScheme
  {
  public:
    typedef std::multimap<ECommand, std::pair<EDevice,EControl> > BindsMap;
    typedef BindsMap::const_iterator                              iterator;

    //�������� ������ �� �������� ����� �����
    static CScheme& Get ();		

    //������� �������� ����� �����
    static void Destroy ();

    //���������������� ����� �����
    void init (ISchemeImpl*);

    //���������� �������� �������-�������
    static std::pair<iterator,iterator> GetCommandBinding (ECommand);  //�������� ������ �������-�������
    static void AddCommandBinding       (ECommand, EDevice, EControl); //�������� ������
    static void RemoveCommandBinding    (ECommand);                    //������� ������
    static bool IsCommandBindingPresent (ECommand);                    //���������� �� ������ ��� ������ �������

    //����������-��������
    static void Load (std::istream &instr);  //�������� ������ �������-�������
    static void Save (std::ostream &outstr); //���������� ������ �������-�������

  private:
    //������ ��� ��������������� ���������
    CScheme ();
   ~CScheme ();

    static CScheme             *ms_pInstance; //��������� �� ����������� ��������� Scheme
    std::auto_ptr<ISchemeImpl>  m_pImpl;      //���������� ���������� ������� �����
    BindsMap                    m_mapBinds;   //������ �������-�������

    //������ ������������ ����������� � ��������� ������������
    CScheme (const CScheme&);
    CScheme& operator= (const CScheme&);
  };
}