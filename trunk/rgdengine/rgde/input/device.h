#pragma once

#include <rgde/input/base.h>

namespace input
{
    //���������� �����
    class Device
    {
    public:
		Device(types::device name, int index, input_impl &input_system);
        virtual ~Device();

		//�������� '���' ����������
        types::device get_name () const {return m_eName;}
		//�������� ���������� ����� ����������
        int		getIndx () const {return m_nIndx;}
		//�������� ���������� �����
        input_impl& getInput()       {return m_rInput;}

		//�������� �������
        Control* get_control       (types::control	eControlName);
        Control* get_control       (const std::wstring &sControlName);

		//���� �� ����� �������
        bool isControlPresent (types::control	eControlName) const;
        bool isControlPresent (const std::wstring &sControlName) const;

    protected:
        friend class input_impl;
        void addButton (types::control controlName); //�������� ������
        void addAxis   (types::control controlName); //�������� ���
        void detachCommand (CommandPtr command); //�������� ������� ��� ���� ���������

    private:
        int         m_nIndx;
        types::device m_eName;
        input_impl &m_rInput;

        std::map<types::control, Control*> m_controls; //��������, ������� ���� � ����������
    };
}