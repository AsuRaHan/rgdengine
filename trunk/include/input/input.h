//input.h
#pragma once
#include <boost/noncopyable.hpp>
#include "input/inputimpl.h"

//�������� ������� �����
namespace input
{
	//////////////////////////////////
	// �������� ����� ������� ����� //
	//////////////////////////////////
	class CInput: boost::noncopyable
	{
	public:
		static CInput& Get  ();  //�������� ������ �� �������� ������� �����
		static void Destroy ();	 //������� �������� ������� �����

		void init (CInputImpl*); //���������������� ������� �����

        /////////////////////////////////
        // ������� ����� ������� ����� //
        /////////////////////////////////
        static bool SetMode (bool exclusive=false, bool foreground=true); //�������� ����� ������ ��������� �����
        static void LoadFromString (const std::string &sXml);      //��������� ���������
        static void LoadFromFile   (const std::string &sFileName); //��������� ���������
        static void Update  ();                        //������� �� ������ ��� ������� �� ��������� �����
        static void Save    (std::string &sXml);       //��������� ���������

        ////////////////////////////////
        // ������ � ����������� ����� //
        ////////////////////////////////
        //�������� ����������
        static CDevice* getDevice (EDevice             eDeviceName, int indx=0);
        static CDevice* getDevice (const std::wstring &sDeviceName, int indx=0);
        //���� �� ����� ����������
        static bool isDevicePresent (EDevice             eDeviceName, int indx=0);
        static bool isDevicePresent (const std::wstring &sDeviceName, int indx=0);

        /////////////////////////////////////
        // ������ � �������� ������� ����� //
        /////////////////////////////////////
        static void      addCommand       (const std::wstring &sCommandName); //�������� �������
        static PCommand  getCommand       (const std::wstring &sCommandName); //�������� �������
        static bool      isCommandPresent (const std::wstring &sCommandName); //���� �� ����� �������
        static void      detachCommand    (PCommand pCommand);                //�������� ������� ��� ���� ���������

	private:
		CInput ();
		~CInput ();

		static CInput            *ms_pInstance; //��������� �� ����������� ��������� System
		std::auto_ptr<CInputImpl> m_pImpl;      //���������� ���������� ������� �����
	};
}
