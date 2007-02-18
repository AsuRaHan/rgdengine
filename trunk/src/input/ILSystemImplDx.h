#pragma once
//���������� ������� ����� ����������� DInput

#define DIRECTINPUT_VERSION 0x0800

#include "input/ILBase.h"
#include "ILSystemImpl.h"
#include <windows.h>
#include <dinput.h>

namespace input
{

	class CSystemImplDx: public ISystemImpl
	{
	public:
		CSystemImplDx (HWND hwnd, bool exclusive=false, bool foreground=true);
		~CSystemImplDx ();

		//������ ������� ����� (��������� ���������� ��
		//��������� ����� � �������� �� �� ���������)
		void update ();

	private:
		LPDIRECTINPUT8       m_pDI;        //���������� DInput
		LPDIRECTINPUTDEVICE8 m_pKeyboard;  //���������� ����� "����������"
		LPDIRECTINPUTDEVICE8 m_pMouse;     //���������� ����� "����"

		void kProcess (DIDEVICEOBJECTDATA dod); //��������� ������������ �������
		void mProcess (DIDEVICEOBJECTDATA dod); //��������� ������� �������
	};

}