//input.cpp
#include "precompiled.h"
#include "input/input.h"
#include "io/io.h"

namespace input
{

    //��������� �� ������������ ���������
    //�� ��������� � ��� ����, �� ��� ����� ��������� �� ���� :)
    CInput* CInput::ms_pInstance = 0;

    //������ ��� ��������������� ���������
    CInput::CInput ()
    {
        assert(!ms_pInstance);
        ms_pInstance = this;
    }

    CInput::~CInput ()
    {
        assert(ms_pInstance);
        ms_pInstance = 0;
    }

    //�������� ��������� �� �������� ������� �����
    CInput& CInput::Get ()
    {
        if (!ms_pInstance)
            ms_pInstance = new CInput;
        return *ms_pInstance;
    }

    //������� �������� ������� �����
    void CInput::Destroy ()
    {
        if (ms_pInstance)
            delete ms_pInstance;
        ms_pInstance = 0;
    }

    //���������������� ������� �����
    void CInput::init (CInputImpl *pImpl)
    {
        m_pImpl.reset(pImpl);
    }

    //�������� ����� ������ ��������� �����
    bool CInput::SetMode (bool exclusive, bool foreground)
    {
        return Get().m_pImpl->SetMode(exclusive,foreground);
    }

    //��������� ���������
    void CInput::LoadFromString (const std::string &sXml)
    {
        Get().m_pImpl->Load(sXml);
    }

    void CInput::LoadFromFile (const std::string &sFileName)
    {
        std::vector<char> data;

        io::CFileSystem &fs    = io::TheFileSystem::Get();
        io::PReadStream stream = fs.findFile(sFileName);
        io::StreamToVector<char>(data, stream);

        Get().m_pImpl->Load(std::string(data.begin(), data.end()));
    }

    //������� �� ������ ��� ������� �� ��������� �����
    void CInput::Update ()
    {
        Get().m_pImpl->Update();
    }

    //��������� ���������
    void CInput::Save (std::string &sXml)
    {
        Get().m_pImpl->Save(sXml);
    }

    //�������� ����������
    CDevice* CInput::getDevice (EDevice eDeviceName, int indx)
    {
        return Get().m_pImpl->getDevice(eDeviceName, indx);
    }

    //�������� ����������
    CDevice* CInput::getDevice (const std::wstring &sDeviceName, int indx)
    {
        return Get().m_pImpl->getDevice(sDeviceName, indx);
    }

    //���� �� ����� ����������
    bool CInput::isDevicePresent (EDevice eDeviceName, int indx)
    {
        return Get().m_pImpl->isDevicePresent(eDeviceName,indx);
    }

    //���� �� ����� ����������
    bool CInput::isDevicePresent (const std::wstring &sDeviceName, int indx)
    {
        return Get().m_pImpl->isDevicePresent(sDeviceName, indx);
    }

    //�������� �������
    void CInput::addCommand (const std::wstring &sCommandName)
    {
        Get().m_pImpl->addCommand(sCommandName);
    }

    //�������� �������
    PCommand CInput::getCommand (const std::wstring &sCommandName)
    {
        return Get().m_pImpl->getCommand(sCommandName);
    }

    //���� �� ����� �������
    bool CInput::isCommandPresent (const std::wstring &sCommandName)
    {
        return Get().m_pImpl->isCommandPresent(sCommandName);
    }

    //�������� ������� ��� ���� ���������
    void CInput::detachCommand (PCommand pCommand)
    {
        Get().m_pImpl->detachCommand(pCommand);
    }

} //namespace input
