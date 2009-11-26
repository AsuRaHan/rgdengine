#include "precompiled.h"

#include <rgde/io/io.h>
#include <rgde/input/input.h>


#include "inputimpl.h"

namespace input
{
    Input* Input::ms_instance = 0;

    //������ ��� ��������������� ���������
    Input::Input ()
    {
        assert(!ms_instance);
        ms_instance = this;
    }

    Input::~Input ()
    {
        assert(ms_instance);
        ms_instance = 0;
    }

    Input& Input::get ()
    {
        if (!ms_instance)
            ms_instance = new Input;
        return *ms_instance;
    }

    void Input::destroy ()
    {
        if (ms_instance)
            delete ms_instance;
        ms_instance = 0;
    }

    void Input::init (input_impl *pImpl)
    {
        m_impl.reset(pImpl);
    }

    bool Input::set_mode (bool exclusive, bool foreground)
    {
        return get().m_impl->set_mode(exclusive,foreground);
    }

    void Input::load_xml (const std::string &xml)
    {
        get().m_impl->load(xml);
    }

    void Input::load (const std::string &file_name)
    {
        std::vector<char> data;

        io::file_system &fs    = io::file_system::get();
        io::readstream_ptr stream = fs.find(file_name);
        io::stream_to_vector<char>(data, stream);

		std::string str( data.begin(), data.end());

        get().m_impl->load(str);
    }

    void Input::update ()
    {
        get().m_impl->update();
    }

    void Input::save_xml (std::string &xml)
    {
        get().m_impl->save(xml);
    }

    device* Input::get_device (device::type eDeviceName, int indx)
    {
        return get().m_impl->get_device(eDeviceName, indx);
    }

    device* Input::get_device (const std::wstring &sDeviceName, int indx)
    {
        return get().m_impl->get_device(sDeviceName, indx);
    }

	Control* Input::get_control(device::type type, int dev_index, controls control)
	{
		if (device* dev = get_device(type, dev_index))
			return dev->get_control(control);

		return NULL;
	}

    //���� �� ����� ����������
    bool Input::is_present (device::type type, int indx)
    {
        return get().m_impl->is_present(type, indx);
    }

    //���� �� ����� ����������
    bool Input::is_present (const std::wstring &sDeviceName, int indx)
    {
        return get().m_impl->is_present(sDeviceName, indx);
    }

    //�������� �������
    void Input::add_command (const std::string &command_name)
    {
        get().m_impl->add_command(command_name);
    }

    //�������� �������
    command_ptr Input::get_command (const std::string &command_name)
    {
        return get().m_impl->get_command(command_name);
    }

    //���� �� ����� �������
    bool Input::is_command_present (const std::string &command_name)
    {
        return get().m_impl->is_command_present(command_name);
    }

    //�������� ������� ��� ���� ���������
    void Input::detach_command (command_ptr pCommand)
    {
        get().m_impl->detach_command(pCommand);
    }
}