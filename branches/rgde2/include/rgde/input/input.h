#pragma once

#include <rgde/input/base.h>
#include <rgde/core/windows_forward.h>
#include <rgde/core/file_system_forward.h>

namespace rgde
{
namespace input
{
	class input_impl;

	// �������� ����� ������� �����
	class system : boost::noncopyable
	{
	public:
		enum mode_flags{
			mode_exlusive = 0x1,
			mode_foreground = 0x4
		};

		system(core::windows::window_ptr window, int flags = mode_foreground);
		~system();

        // ������� ����� ������� �����
        bool set_mode (int flags = mode_foreground);
		
		//��������� ���������
        void load (const std::string &xml_str);
		void load (core::vfs::istream_ptr src);

		// save input layout to string
		void save(std::string &xml_str);
        
		//������� �� ������ ��� ������� �� ��������� �����
		void update();
        
        // get input device
        device* get_device (types::EDevice device_type, int indx=0);
        device* get_device (const std::wstring &device_name, int indx=0);

        // check is device present
        bool is_device_present (types::EDevice device_type, int indx=0);
        bool is_device_present (const std::wstring &device_name, int indx=0);

		control* get_control(types::EDevice device, int dev_index, types::EControl control);
		control* get_control(types::EDevice device, types::EControl control)
		{
			return get_control(device, 0, control);
		}

        // ������ � �������� ������� �����
        void add_command       (const std::wstring &command_name); //�������� �������
        command_ptr  get_command       (const std::wstring &command_name); //�������� �������
        bool is_command_present (const std::wstring &command_name); //���� �� ����� �������
        void detach_command    (command_ptr command);                //�������� ������� ��� ���� ���������

	private:
		std::auto_ptr<input_impl> m_impl;      //���������� ���������� ������� �����
	};
}
}