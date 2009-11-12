#pragma once
#include <rgde/input/base.h>

#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dinput.h>

namespace input
{
    class input_impl
    {
    public:
        input_impl();
       ~input_impl();

	    //�������� ����� ������ ��������� �����
        bool set_mode (bool exclusive=false, bool foreground=true);

		//������������������� ������� �����
        bool init    (HWND hWnd, bool exclusive=false, bool foreground=true);

		//���������/��������� ���������
        void Load(const std::string &sXml);                               
		void Save(std::string &sXml);

		//������� �� ������ ��� ������� �� ��������� �����
        void update();
		//��������� ������ ������� �����
        void Done();

        //�������� ����������
        device* get_device(types::device      eDeviceName, int indx=0);
        device* get_device(const std::wstring &sDeviceName, int indx=0);

        //���� �� ����� ����������
        bool is_present(types::device      eDeviceName, int indx=0) const;
        bool is_present(const std::wstring &sDeviceName, int indx=0) const;


        // ������ � �������� ������� �����
		//�������� �������
        command_ptr add_command(const std::wstring &command_name);
		//�������� �������
        command_ptr getCommand(const std::wstring &command_name);
		//���� �� ����� �������
        bool isCommandPresent(const std::wstring &command_name) const;
		//�������� ������� ��� ���� ���������
        void detach_command(command_ptr pCommand);

	private:
		input_impl (const input_impl&);
		input_impl& operator= (const input_impl&);

		bool init_input(HWND hWnd, bool exclusive, bool foreground);
		void doneDXInput();

		//��������� ������������ �������
		void kProcess (DIDEVICEOBJECTDATA data);
		//��������� ������� �������
		void mProcess (DIDEVICEOBJECTDATA data);

    private:
        std::list<device*> m_devices;
        std::list<command_ptr> m_commands;
		
		//��������������� ���������� ��� ����� �������� �������
        device* keyboard; 
        device* mouse;    

        bool m_bInit;

        HWND m_hWnd;
        bool m_exclusive;
        bool m_foreground;

		LPDIRECTINPUT8       m_pDI;       //���������� DInput
		LPDIRECTINPUTDEVICE8 m_pKeyboard; //���������� ����� "����������"
		LPDIRECTINPUTDEVICE8 m_pMouse;    //���������� ����� "����"
    };
}