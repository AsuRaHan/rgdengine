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
		static void Destroy ();

		void init (input_impl*);

        // ������� ����� ������� �����
        static bool SetMode (bool exclusive=false, bool foreground=true); //�������� ����� ������ ��������� �����
        static void LoadFromString (const std::string &sXml);      //��������� ���������
        static void LoadFromFile   (const std::string &sFileName); //��������� ���������
        static void update  ();                        //������� �� ������ ��� ������� �� ��������� �����
        static void Save    (std::string &sXml);       //��������� ���������

        // ������ � ����������� �����
        //�������� ����������
        static Device* getDevice (types::device eDeviceName, int indx=0);
        static Device* getDevice (const std::wstring &sDeviceName, int indx=0);
        //���� �� ����� ����������
        static bool isDevicePresent (types::device eDeviceName, int indx=0);
        static bool isDevicePresent (const std::wstring &sDeviceName, int indx=0);

		static Control* GetControl(types::device device, int dev_index, types::control control);
		static Control* GetControl(types::device device, types::control control)
		{
			return GetControl(device, 0, control);
		}

        // ������ � �������� ������� �����
        static void      addCommand       (const std::wstring &sCommandName); //�������� �������
        static CommandPtr  getCommand       (const std::wstring &sCommandName); //�������� �������
        static bool      isCommandPresent (const std::wstring &sCommandName); //���� �� ����� �������
        static void      detachCommand    (CommandPtr pCommand);                //�������� ������� ��� ���� ���������

	private:
		Input();
		~Input();

		static Input            *ms_instance; //��������� �� ����������� ��������� System
		std::auto_ptr<input_impl> m_pImpl;      //���������� ���������� ������� �����
	};
}
