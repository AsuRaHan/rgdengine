#pragma once

#include "input/base.h"

namespace input
{
    //���������� �����
    class Device
    {
    public:
		Device(types::EDevice name, int index, InputImpl &input_system);
        virtual ~Device();

		//�������� '���' ����������
        types::EDevice getName () const {return m_eName;}
		//�������� ���������� ����� ����������
        int		getIndx () const {return m_nIndx;}
		//�������� ���������� �����
        InputImpl& getInput()       {return m_rInput;}

		//�������� �������
        Control* getControl       (types::EControl	eControlName);
        Control* getControl       (const std::wstring &sControlName);

		//���� �� ����� �������
        bool isControlPresent (types::EControl	eControlName) const;
        bool isControlPresent (const std::wstring &sControlName) const;

    protected:
        friend class InputImpl;
        void addButton (types::EControl controlName); //�������� ������
        void addAxis   (types::EControl controlName); //�������� ���
        void detachCommand (CommandPtr command); //�������� ������� ��� ���� ���������

    private:
        int         m_nIndx;
        types::EDevice m_eName;
        InputImpl &m_rInput;

        std::map<types::EControl, Control*> m_controls; //��������, ������� ���� � ����������
    };
}