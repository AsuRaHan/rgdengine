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
        void load(const std::string &xml);                               
		void save(std::string &xml);

		//������� �� ������ ��� ������� �� ��������� �����
        void update();
		//��������� ������ ������� �����
        void Done();

        device* get_device(types::device      eDeviceName, int indx=0);
        device* get_device(const std::wstring &sDeviceName, int indx=0);

        bool is_present(types::device      eDeviceName, int indx=0) const;
        bool is_present(const std::wstring &sDeviceName, int indx=0) const;


        command_ptr add_command(const std::wstring &command_name);
        command_ptr get_command(const std::wstring &command_name);
        bool is_command_present(const std::wstring &command_name) const;
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
		typedef std::list<device*> devices_list;
        devices_list m_devices;

		typedef std::list<command_ptr> commands_list;
		typedef commands_list::const_iterator commands_iter;

        commands_list m_commands;
		
		// for fast acsess
        device* keyboard; 
        device* mouse;    

        bool m_inited;

        HWND m_hwnd;
        bool m_exclusive;
        bool m_foreground;

		LPDIRECTINPUT8       m_dxinput;       //���������� DInput
		LPDIRECTINPUTDEVICE8 m_keyboard; //���������� ����� "����������"
		LPDIRECTINPUTDEVICE8 m_mouse;    //���������� ����� "����"
    };
}