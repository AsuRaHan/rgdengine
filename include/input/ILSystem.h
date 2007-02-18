#pragma once

#include <boost/noncopyable.hpp>

#include "input/ILBase.h"

//�������� ������� �����
namespace input
{
	//////////////////////////////////
	// �������� ����� ������� ����� //
	//////////////////////////////////
	class CSystem : boost::noncopyable
	{
	public:
		static CSystem& Get (); //�������� ������ �� �������� ������� �����
		static void Destroy ();	//������� �������� ������� �����

		void init (ISystemImpl*);	//���������������� ������� �����

		//������ � ����������� �����
		static CDevice* GetDevice       (EDevice); //�������� ����������
		static bool     IsDevicePresent (EDevice); //���������, ���������� �� ��������� ����������

		//������ � ���������
		static CControl* GetControl       (EDevice, EControl); //�������� �������
		static bool      IsControlPresent (EDevice, EControl); //���������, ���������� �� ���������� �������

		//������ ������� ����� (��������� ���������� ��
		//��������� ����� � �������� �� �� ���������)
		static void Update ();

	private:
		CSystem ();
		~CSystem ();

		static CSystem            *ms_pInstance; //��������� �� ����������� ��������� System
		std::auto_ptr<ISystemImpl> m_pImpl;      //���������� ���������� ������� �����
	};
}