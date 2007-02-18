//ILScheme.h
#include "precompiled.h"

#include "input/ILScheme.h"
#include "input/ILSchemeImpl.h"

namespace input
{
  //��������� �� ������������ ���������
  //�� ��������� � ��� ����, �� ��� ����� ��������� �� ���� :)
  CScheme* CScheme::ms_pInstance = 0;

  CScheme::CScheme ()
  {
    assert(!ms_pInstance);
    ms_pInstance = this;
  }

  CScheme::~CScheme ()
  {
    assert(ms_pInstance);
    ms_pInstance = 0;
  }

  CScheme& CScheme::Get ()
  {
    if (!ms_pInstance)
      ms_pInstance = new CScheme;
    return *ms_pInstance;
  }

  void CScheme::Destroy ()
  {
    if (ms_pInstance)
      delete ms_pInstance;

    ms_pInstance = 0;
  }

  void CScheme::init (ISchemeImpl *pImpl)
  {
    m_pImpl.reset(pImpl);
  }

  //�������� ������ �������-�������
  std::pair<CScheme::iterator,CScheme::iterator> CScheme::GetCommandBinding (ECommand eCommand)
  {
    return std::make_pair<iterator,iterator>
    (
      CScheme::Get().m_mapBinds.lower_bound(eCommand),
      CScheme::Get().m_mapBinds.upper_bound(eCommand)
    );
  }

  //�������� ������
  void CScheme::AddCommandBinding (ECommand eCommand, EDevice eDevice, EControl eControl)
  {
    CScheme::Get().m_mapBinds.insert
    (
      std::make_pair<ECommand, std::pair<EDevice, EControl> >
      (
        eCommand,
        std::make_pair<EDevice, EControl>(eDevice,eControl)
      )
    );
  }

  //������� ������
  void CScheme::RemoveCommandBinding (ECommand eCommand)
  {
    CScheme::Get().m_mapBinds.erase(eCommand);
  }

  //���������� �� ������ ��� ������ �������
  bool CScheme::IsCommandBindingPresent (ECommand eCommand)
  {
    return CScheme::Get().m_mapBinds.lower_bound(eCommand) !=
           CScheme::Get().m_mapBinds.upper_bound(eCommand);
  }

  //�������� ������ �������-�������
  void CScheme::Load (std::istream &instr)
  {
    CScheme::Get().m_pImpl->load(instr);
  }

  //���������� ������ �������-�������
  void CScheme::Save (std::ostream &outstr)
  {
    CScheme::Get().m_pImpl->save(outstr);
  }

} //namespace input
