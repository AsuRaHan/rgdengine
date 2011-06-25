#pragma once
#include <rgde/input/base.h>

#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dinput.h>

namespace rgde
{
namespace input
{
    class input_impl
    {
    public:
        input_impl(core::windows::window_ptr window, bool exclusive=false, bool foreground=true);
       ~input_impl();

	    //�������� ����� ������ ��������� �����
        bool set_mode (bool exclusive=false, bool foreground=true);

		//���������/��������� ���������
        void load(const std::string &xml_str);                               
		void save(std::string &xml_str);

		//������� �� ������ ��� ������� �� ��������� �����
        void update();
		//��������� ������ ������� �����
        void done();

        //�������� ����������
        device* get_device(types::EDevice      device_type, int indx=0);
        device* get_device(const std::wstring &device_name, int indx=0);

        //���� �� ����� ����������
        bool is_device_present(types::EDevice      device_type, int indx=0) const;
        bool is_device_present(const std::wstring &device_name, int indx=0) const;

        // ������ � �������� ������� �����
		//�������� �������
        command_ptr add_command(const std::wstring &command_name);
		//�������� �������
        command_ptr get_command(const std::wstring &command_name);
		//���� �� ����� �������
        bool is_command_present(const std::wstring &command_name) const;
		//�������� ������� ��� ���� ���������
        void detach_command(command_ptr command);

	private:
		input_impl (const input_impl&);
		input_impl& operator= (const input_impl&);

		bool init_dx_input(HWND hWnd, bool exclusive, bool foreground);
		void done_dx_input();

		//��������� ������������ �������
		void process_keyboard (DIDEVICEOBJECTDATA data);
		//��������� ������� �������
		void process_mouse (DIDEVICEOBJECTDATA data);

    private:
        std::list<device*> m_devices;
        std::list<command_ptr> m_commands;
		
		//��������������� ���������� ��� ����� �������� �������
        device*            keyboard; 
        device*            mouse;    

        bool m_inited;

        HWND m_hwnd;
        bool m_exclusive;
        bool m_foreground;

		LPDIRECTINPUT8       m_direct_input;       //���������� DInput
		LPDIRECTINPUTDEVICE8 m_dx_keyboard; //���������� ����� "����������"
		LPDIRECTINPUTDEVICE8 m_dx_mouse;    //���������� ����� "����"
    };
}
}