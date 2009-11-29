#include "stdafx.h"


#include <rgde/input/input.h>
#include <rgde/input/device.h>

#include <rgde/core/windows.h>

#include "inputimpl.h"

namespace rgde
{
namespace input
{
    system::system (core::windows::window_ptr window, bool exclusive, bool foreground)
    {
		HWND hwnd = (HWND)window->get_handle();
		m_impl.reset(new input_impl(hwnd, exclusive, foreground));
    }

    system::~system ()
    {
    }

    bool system::set_mode(bool exclusive, bool foreground)
    {
        return m_impl->set_mode(exclusive,foreground);
    }

    void system::load_from_string (const std::string &xml_str)
    {
        m_impl->load(xml_str);
    }

    void system::load_from_file (const std::string &file_name)
    {
        std::vector<char> data;

        //io::CFileSystem &fs    = io::TheFileSystem::get();
        //io::readstream_ptr stream = fs.findFile(file_name);
        //io::stream_to_vector<char>(data, stream);

        //m_impl->load(std::string(data.begin(), data.end()));
    }

    void system::update ()
    {
        m_impl->update();
    }

    void system::save (std::string &xml_str)
    {
        m_impl->save(xml_str);
    }

    device* system::get_device (types::EDevice device_type, int indx)
    {
        return m_impl->get_device(device_type, indx);
    }

    device* system::get_device (const std::wstring &device_name, int indx)
    {
        return m_impl->get_device(device_name, indx);
    }

	control* system::get_control(types::EDevice type, int index, types::EControl control)
	{
		if (device* dev = get_device(type, index))
			return dev->get_control(control);

		return NULL;
	}

    //���� �� ����� ����������
    bool system::is_device_present (types::EDevice device_type, int indx)
    {
        return m_impl->is_device_present(device_type,indx);
    }

    //���� �� ����� ����������
    bool system::is_device_present (const std::wstring &device_name, int indx)
    {
        return m_impl->is_device_present(device_name, indx);
    }

    //�������� �������
    void system::add_command (const std::wstring &command_name)
    {
        m_impl->add_command(command_name);
    }

    //�������� �������
    command_ptr system::get_command (const std::wstring &command_name)
    {
        return m_impl->get_command(command_name);
    }

    //���� �� ����� �������
    bool system::is_command_present (const std::wstring &command_name)
    {
        return m_impl->is_command_present(command_name);
    }

    //�������� ������� ��� ���� ���������
    void system::detach_command (command_ptr command)
    {
        m_impl->detach_command(command);
    }
}
}