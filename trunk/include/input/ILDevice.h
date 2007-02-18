#pragma once

#include <map>

#include "input/ILBase.h"


namespace input
{
	class CControl;

	//////////////////////
	// ���������� ����� //
	//////////////////////
	class CDevice
	{
		friend class ISystemImpl;

	public:
		~CDevice ();

		EDevice  getName () const {return m_eName;} //�������� '���' ����������

		CControl* getControl       (EControl); //�������� �������
		bool      isControlPresent (EControl); //���� �� ����� �������

	protected:
		CDevice (EDevice eName): m_eName(eName) {}

	private:
		EDevice                      m_eName;       //'���' ����������
		std::map<EControl,CControl*> m_mapControls; //��������, ������� ���� � ����������
	};
}