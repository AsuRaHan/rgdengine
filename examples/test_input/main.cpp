#define _WIN32_WINNT 0x0500 //��� ����, ����� ���������� GetConsoleWindow
#include <windows.h>        //��� GetConsoleWindow � SetWindowText
#include <stdio.h>          //��� wsprintf

//RGDE
#include "input/IL.h"                 //���������� �����
#include "../src/input/ILSystemImplDx.h"     //������������� ����� ��� ������ DInput
#include "../src/input/ILSchemeImplSimple.h" //������������� ��������� �������-�������

//STL
#include <iostream>

//�������� �����
class CTest
{
public:
	CTest ();
	int  m_nCounter;
	bool m_bQuit;
	void update ();

private:
	//������ ���� ������
	input::CButtonCommand       m_cEsc;
	input::CButtonCommand       m_cButtonCommand;
	input::CTriggerCommand      m_cTriggerCommand;
	input::CRelativeAxisCommand m_cRelativeAxisCommand;
	input::CAbsoluteAxisCommand m_cAbsoluteAxisCommand;

	//����������� ��� ������
	void onEsc                 (const input::CButtonEvent&);
	void onCommand             (const input::CEvent&);
	void onButtonCommand       (const input::CButtonEvent&);
	void onTriggerCommand      (const input::CTriggerEvent&);
	void onRelativeAxisCommand (const input::CRelativeAxisEvent&);
	void onAbsoluteAxisCommand (const input::CAbsoluteAxisEvent&);
};


int main ()
{
	//��-����, ���� ���������� ����� ���� ������ ����������
	HWND hwnd = GetConsoleWindow();

	//������� ��������� ��� ������� �����
	input::CSystem::Get().init( new input::CSystemImplDx(hwnd) );
	input::CScheme::Get().init( new input::CSchemeImplSimple() );

	CTest cTest;
	while (!cTest.m_bQuit)
	{
		input::CSystem::Update();
		cTest.update();
		Sleep(10);
	}

	//������� ��������� ������� �����
	input::CScheme::Destroy();
	input::CSystem::Destroy();
	return 0;
}

CTest::CTest (): m_bQuit(false), m_nCounter(0)
{
	//����� ���������� �������� ������ � ��������� ���� ��� �������:
	//1) �������� ��������� � ������� ������� � �������
	//CSchema::Load(from); //from - std::istream
	//
	//m_cButtonCommand.      attachToControl (CommandUp       );
	//m_cTriggerCommand.     attachToControl (CommandDown     );
	//m_cRelativeAxisCommand.attachToControl (CommandRotateCW );
	//m_cAbsoluteAxisCommand.attachToControl (CommandRotateCCW);

	//2) ���� ������� ������ ������� � ����������
	m_cEsc.                attachToControl (input::Keyboard, input::KeyEscape);
	//���� ������� ����� ��������� � ����������� ���������� ������������
	m_cButtonCommand.      attachToControl (input::Keyboard, input::KeyUp);
	m_cButtonCommand.      attachToControl (input::Keyboard, input::KeyDown);
	m_cButtonCommand.      attachToControl (input::Keyboard, input::KeyLeft);
	m_cButtonCommand.      attachToControl (input::Keyboard, input::KeyRight);

	//� ������� ����� ����������� �������� �� ������ ���������
	m_cTriggerCommand.     attachToControl (input::Keyboard, input::KeySpace);
	m_cTriggerCommand.     attachToControl (input::Mouse,    input::ButtonRight);
	
	//��� ����� �������� ������������� � ����������
	m_cRelativeAxisCommand.attachToControl (input::Mouse,    input::AxisX);
	m_cAbsoluteAxisCommand.attachToControl (input::Mouse,    input::AxisY);

	//����� �������� ������� � ��������� ����� ��������� �������� �����������
	m_cEsc.                addHandler(this,&CTest::onEsc);
	m_cButtonCommand.      addHandler(this,&CTest::onButtonCommand);
	m_cTriggerCommand.     addHandler(this,&CTest::onTriggerCommand);
	m_cRelativeAxisCommand.addHandler(this,&CTest::onRelativeAxisCommand);
	m_cAbsoluteAxisCommand.addHandler(this,&CTest::onAbsoluteAxisCommand);

	//��������� ������ ����� ��������� � ������ � ���� �� �����������
	m_cButtonCommand.      addHandler(this,&CTest::onCommand);
	m_cTriggerCommand.     addHandler(this,&CTest::onCommand);
	m_cRelativeAxisCommand.addHandler(this,&CTest::onCommand);
	m_cAbsoluteAxisCommand.addHandler(this,&CTest::onCommand);
}

void CTest::update ()
{
	//����� ���������� ��������� ������
	WCHAR buf[256];

	wsprintf
		(
		buf,
		L"trigger=%s coord=%d counter=%d (press Esc for quit)",
		m_cTriggerCommand ? L"on" : L"off", //� ����� ��������� ������� (���/����)
		m_cAbsoluteAxisCommand.getCoord(),  //����� ���������� � ���������� ���
		m_nCounter
		);

	SetWindowText(GetConsoleWindow(),buf);
}

void CTest::onEsc (const input::CButtonEvent&)
{
	m_bQuit = true;
}

void CTest::onCommand (const input::CEvent&)
{
	m_nCounter++;
}

void CTest::onButtonCommand (const input::CButtonEvent&)
{
	std::cout << "ButtonCommand\n";
}

void CTest::onTriggerCommand (const input::CTriggerEvent&)
{
	std::cout << "TriggerCommand\n";
}

void CTest::onRelativeAxisCommand (const input::CRelativeAxisEvent&)
{
	std::cout << "RelativeAxisCommand\n";
}

void CTest::onAbsoluteAxisCommand (const input::CAbsoluteAxisEvent&)
{
	std::cout << "AbsoluteAxisCommand\n";
}