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
        static void Save    (std::string &sXml);       //��������� ���������

        // ������ � ����������� �����
        //�������� ����������
        static device_dx9* get_device (types::device eDeviceName, int indx=0);
        static device_dx9* get_device (const std::wstring &sDeviceName, int indx=0);
        //���� �� ����� ����������
        static bool is_present (types::device eDeviceName, int indx=0);
        static bool is_present (const std::wstring &sDeviceName, int indx=0);

		static Control* GetControl(types::device device, int dev_index, types::control control);
		static Control* GetControl(types::device device, types::control control)
		{
			return GetControl(device, 0, control);
		}

        // ������ � �������� ������� �����
        static void      add_command       (const std::wstring &command_name); //�������� �������
        static command_ptr  getCommand       (const std::wstring &command_name); //�������� �������
        static bool      isCommandPresent (const std::wstring &command_name); //���� �� ����� �������
        static void      detach_command    (command_ptr pCommand);                //�������� ������� ��� ���� ���������

	private:
		Input();
		~Input();

		static Input            *ms_instance; //��������� �� ����������� ��������� System
		std::auto_ptr<input_impl> m_pImpl;      //���������� ���������� ������� �����
	};
}
