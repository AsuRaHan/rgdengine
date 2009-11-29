#pragma once

#include <rgde/input/base.h>

namespace input
{
	class input_impl;

	// �������� ����� ������� �����
	class Input: boost::noncopyable
	{
	public:
		static Input& get  ();
		static void destroy ();

		void init (input_impl*);

        // ������� ����� ������� �����
        static bool set_mode (bool exclusive=false, bool foreground=true); //�������� ����� ������ ��������� �����
        static void LoadFromString (const std::string &sXml);      //��������� ���������
        static void LoadFromFile   (const std::string &sFileName); //��������� ���������
        static void update  ();                        //������� �� ������ ��� ������� �� ��������� �����
        static void save    (std::string &sXml);       //��������� ���������

        // ������ � ����������� �����
        //�������� ����������
        static device* get_device (types::EDevice eDeviceName, int indx=0);
        static device* get_device (const std::wstring &device_name, int indx=0);
        //���� �� ����� ����������
        static bool is_device_present (types::EDevice eDeviceName, int indx=0);
        static bool is_device_present (const std::wstring &device_name, int indx=0);

		static control* GetControl(types::EDevice device, int dev_index, types::EControl control);
		static control* GetControl(types::EDevice device, types::EControl control)
		{
			return GetControl(device, 0, control);
		}

        // ������ � �������� ������� �����
        static void      add_command       (const std::wstring &command_name); //�������� �������
        static command_ptr  get_command       (const std::wstring &command_name); //�������� �������
        static bool      isCommandPresent (const std::wstring &command_name); //���� �� ����� �������
        static void      detach_command    (command_ptr pCommand);                //�������� ������� ��� ���� ���������

	private:
		Input();
		~Input();

		static Input            *ms_instance; //��������� �� ����������� ��������� System
		std::auto_ptr<input_impl> m_pImpl;      //���������� ���������� ������� �����
	};
}