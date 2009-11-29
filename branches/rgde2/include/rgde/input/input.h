#pragma once

#include <rgde/input/base.h>

namespace input
{
	class input_impl;

	// �������� ����� ������� �����
	class system: boost::noncopyable
	{
	public:
		static system& get  ();
		static void destroy ();

		void init (input_impl*);

        // ������� ����� ������� �����
        static bool set_mode (bool exclusive=false, bool foreground=true); //�������� ����� ������ ��������� �����
        static void load_from_string (const std::string &xml_str);      //��������� ���������
        static void load_from_file   (const std::string &file_name); //��������� ���������
        static void update  ();                        //������� �� ������ ��� ������� �� ��������� �����
        static void save    (std::string &xml_str);       //��������� ���������

        // ������ � ����������� �����
        //�������� ����������
        static device* get_device (types::EDevice device_type, int indx=0);
        static device* get_device (const std::wstring &device_name, int indx=0);
        //���� �� ����� ����������
        static bool is_device_present (types::EDevice device_type, int indx=0);
        static bool is_device_present (const std::wstring &device_name, int indx=0);

		static control* get_control(types::EDevice device, int dev_index, types::EControl control);
		static control* get_control(types::EDevice device, types::EControl control)
		{
			return get_control(device, 0, control);
		}

        // ������ � �������� ������� �����
        static void			add_command       (const std::wstring &command_name); //�������� �������
        static command_ptr  get_command       (const std::wstring &command_name); //�������� �������
        static bool			is_command_present (const std::wstring &command_name); //���� �� ����� �������
        static void			detach_command    (command_ptr command);                //�������� ������� ��� ���� ���������

	private:
		system();
		~system();

		static system            *ms_instance; //��������� �� ����������� ��������� System
		std::auto_ptr<input_impl> m_impl;      //���������� ���������� ������� �����
	};
}