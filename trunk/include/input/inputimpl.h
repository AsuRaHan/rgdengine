//inputimpl.h
#pragma once
#include "base.h"

#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dinput.h>

namespace input
{

    //������� �����
    class CInputImpl
    {
    public:
        CInputImpl();
       ~CInputImpl();

        /////////////////////////////////////////////////
        // �������� ������ ��� ������ � �������� ����� //
        /////////////////////////////////////////////////
        bool SetMode (bool exclusive=false, bool foreground=true);            //�������� ����� ������ ��������� �����
        bool Init    (HWND hWnd, bool exclusive=false, bool foreground=true); //������������������� ������� �����
        void Load    (const std::string &sXml);                               //��������� ���������
        void Update  ();                                                      //������� �� ������ ��� ������� �� ��������� �����
        void Save    (std::string &sXml);                                     //��������� ���������
        void Done    ();                                                      //��������� ������ ������� �����

        ////////////////////////////////
        // ������ � ����������� ����� //
        ////////////////////////////////
        //�������� ����������
        CDevice* getDevice (EDevice             eDeviceName, int indx=0);
        CDevice* getDevice (const std::wstring &sDeviceName, int indx=0);
        //���� �� ����� ����������
        bool isDevicePresent (EDevice             eDeviceName, int indx=0) const;
        bool isDevicePresent (const std::wstring &sDeviceName, int indx=0) const;

        /////////////////////////////////////
        // ������ � �������� ������� ����� //
        /////////////////////////////////////
        void      addCommand       (const std::wstring &sCommandName);       //�������� �������
        PCommand  getCommand       (const std::wstring &sCommandName);       //�������� �������
        bool      isCommandPresent (const std::wstring &sCommandName) const; //���� �� ����� �������
        void      detachCommand    (PCommand pCommand);                      //�������� ������� ��� ���� ���������

    private:
        std::list<CDevice*> m_devices;
        std::list<PCommand> m_commands;
        CDevice*            keyboard; //��������������� ����������
        CDevice*            mouse;    //��� ����� �������� �������

        bool m_bInit;

    private:
        CInputImpl (const CInputImpl&);
        CInputImpl& operator= (const CInputImpl&);

    private:
        HWND m_hWnd;
        bool m_exclusive;
        bool m_foreground;

        bool initDXInput(HWND hWnd, bool exclusive, bool foreground);
        void doneDXInput();

		LPDIRECTINPUT8       m_pDI;       //���������� DInput
		LPDIRECTINPUTDEVICE8 m_pKeyboard; //���������� ����� "����������"
		LPDIRECTINPUTDEVICE8 m_pMouse;    //���������� ����� "����"

		void kProcess (DIDEVICEOBJECTDATA dod); //��������� ������������ �������
		void mProcess (DIDEVICEOBJECTDATA dod); //��������� ������� �������
    };

}