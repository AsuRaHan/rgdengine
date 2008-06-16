#pragma once
#include "base.h"

#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dinput.h>

namespace input
{
    class InputImpl
    {
    public:
        InputImpl();
       ~InputImpl();

	    //�������� ����� ������ ��������� �����
        bool SetMode (bool exclusive=false, bool foreground=true);

		//������������������� ������� �����
        bool Init    (HWND hWnd, bool exclusive=false, bool foreground=true);

		//���������/��������� ���������
        void Load(const std::string &sXml);                               
		void Save(std::string &sXml);

		//������� �� ������ ��� ������� �� ��������� �����
        void Update();
		//��������� ������ ������� �����
        void Done();

        //�������� ����������
        Device* getDevice(types::EDevice      eDeviceName, int indx=0);
        Device* getDevice(const std::wstring &sDeviceName, int indx=0);

        //���� �� ����� ����������
        bool isDevicePresent(types::EDevice      eDeviceName, int indx=0) const;
        bool isDevicePresent(const std::wstring &sDeviceName, int indx=0) const;


        // ������ � �������� ������� �����
		//�������� �������
        CommandPtr addCommand(const std::wstring &sCommandName);
		//�������� �������
        CommandPtr getCommand(const std::wstring &sCommandName);
		//���� �� ����� �������
        bool isCommandPresent(const std::wstring &sCommandName) const;
		//�������� ������� ��� ���� ���������
        void detachCommand(CommandPtr pCommand);

	private:
		InputImpl (const InputImpl&);
		InputImpl& operator= (const InputImpl&);

		bool initDXInput(HWND hWnd, bool exclusive, bool foreground);
		void doneDXInput();

		//��������� ������������ �������
		void kProcess (DIDEVICEOBJECTDATA data);
		//��������� ������� �������
		void mProcess (DIDEVICEOBJECTDATA data);

    private:
        std::list<Device*> m_devices;
        std::list<CommandPtr> m_commands;
		
		//��������������� ���������� ��� ����� �������� �������
        Device*            keyboard; 
        Device*            mouse;    

        bool m_bInit;

        HWND m_hWnd;
        bool m_exclusive;
        bool m_foreground;

		LPDIRECTINPUT8       m_pDI;       //���������� DInput
		LPDIRECTINPUTDEVICE8 m_pKeyboard; //���������� ����� "����������"
		LPDIRECTINPUTDEVICE8 m_pMouse;    //���������� ����� "����"
    };
}