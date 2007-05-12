#include "precompiled.h"

#include "input/input.h"
#include "input/inputimpl.h"

#include "io/io.h"

namespace input
{
    Input* Input::ms_pInstance = 0;

    //������ ��� ��������������� ���������
    Input::Input ()
    {
        assert(!ms_pInstance);
        ms_pInstance = this;
    }

    Input::~Input ()
    {
        assert(ms_pInstance);
        ms_pInstance = 0;
    }

    Input& Input::Get ()
    {
        if (!ms_pInstance)
            ms_pInstance = new Input;
        return *ms_pInstance;
    }

    //������� �������� ������� �����
    void Input::Destroy ()
    {
        if (ms_pInstance)
            delete ms_pInstance;
        ms_pInstance = 0;
    }

    //���������������� ������� �����
    void Input::init (InputImpl *pImpl)
    {
        m_pImpl.reset(pImpl);
    }

    bool Input::SetMode (bool exclusive, bool foreground)
    {
        return Get().m_pImpl->SetMode(exclusive,foreground);
    }

    void Input::LoadFromString (const std::string &sXml)
    {
        Get().m_pImpl->Load(sXml);
    }

    void Input::LoadFromFile (const std::string &sFileName)
    {
        std::vector<char> data;

        io::CFileSystem &fs    = io::TheFileSystem::Get();
        io::PReadStream stream = fs.findFile(sFileName);
        io::StreamToVector<char>(data, stream);

        Get().m_pImpl->Load(std::string(data.begin(), data.end()));
    }

    void Input::Update ()
    {
        Get().m_pImpl->Update();
    }

    void Input::Save (std::string &sXml)
    {
        Get().m_pImpl->Save(sXml);
    }

    Device* Input::getDevice (types::EDevice eDeviceName, int indx)
    {
        return Get().m_pImpl->getDevice(eDeviceName, indx);
    }

    Device* Input::getDevice (const std::wstring &sDeviceName, int indx)
    {
        return Get().m_pImpl->getDevice(sDeviceName, indx);
    }

    //���� �� ����� ����������
    bool Input::isDevicePresent (types::EDevice eDeviceName, int indx)
    {
        return Get().m_pImpl->isDevicePresent(eDeviceName,indx);
    }

    //���� �� ����� ����������
    bool Input::isDevicePresent (const std::wstring &sDeviceName, int indx)
    {
        return Get().m_pImpl->isDevicePresent(sDeviceName, indx);
    }

    //�������� �������
    void Input::addCommand (const std::wstring &sCommandName)
    {
        Get().m_pImpl->addCommand(sCommandName);
    }

    //�������� �������
    CommandPtr Input::getCommand (const std::wstring &sCommandName)
    {
        return Get().m_pImpl->getCommand(sCommandName);
    }

    //���� �� ����� �������
    bool Input::isCommandPresent (const std::wstring &sCommandName)
    {
        return Get().m_pImpl->isCommandPresent(sCommandName);
    }

    //�������� ������� ��� ���� ���������
    void Input::detachCommand (CommandPtr pCommand)
    {
        Get().m_pImpl->detachCommand(pCommand);
    }
}