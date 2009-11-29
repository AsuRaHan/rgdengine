#pragma once

#include <rgde/input/base.h>

namespace input
{
    //���������� �����
    class Device
    {
    public:
		Device(types::EDevice name, int index, input_impl &input_system);
        virtual ~Device();

		//�������� '���' ����������
        types::EDevice getName () const {return m_eName;}
		//�������� ���������� ����� ����������
        int		getIndx () const {return m_nIndx;}
		//�������� ���������� �����
        input_impl& getInput()       {return m_rInput;}

		//�������� �������
        Control* get_control       (types::EControl	eControlName);
        Control* get_control       (const std::wstring &sControlName);

		//���� �� ����� �������
        bool isControlPresent (types::EControl	eControlName) const;
        bool isControlPresent (const std::wstring &sControlName) const;

    protected:
        friend class input_impl;
        void addButton (types::EControl controlName); //�������� ������
        void addAxis   (types::EControl controlName); //�������� ���
        void detachCommand (CommandPtr command); //�������� ������� ��� ���� ���������

    private:
        int         m_nIndx;
        types::EDevice m_eName;
        input_impl &m_rInput;

        std::map<types::EControl, Control*> m_controls; //��������, ������� ���� � ����������
    };
}