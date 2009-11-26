#pragma once

#include <rgde/input/base.h>

namespace input
{
    //������� (������, ��� � �.�.) ���������� �����
    class Control
    {
    public:        
        //���� ���������
        enum type
        {
            Button,
            Axis
        };

        Control(controls name, type type, device &device);

        controls get_name () const {return m_name;}
		type    get_type () const {return m_type;}

        //�������� �����������
        void bind (command_ptr command);
        void bind (const std::wstring &command_name);

        //������� �����������
        void unbind (command_ptr command);
        void unbind (const std::wstring &command_name);

        //�������� �� ����� �����������
        bool is_bind (command_ptr command);
        bool is_bind (const std::wstring &command_name);

        //��������� ������������ � ����� ���������
        void notify_all (); 

		bool getPress() const {return m_press;}

        int  m_time;
        bool m_press;
        int  m_delta;

    private:
        device          &m_device; //����������, �������� ����������� �������
        type            m_type;   //��� ��������
        controls  m_name;   //'���' ��������

		typedef std::list<command_ptr> CommandsList;
		typedef CommandsList::iterator commands_iter;

		//�������, � ������� �������� �������
        CommandsList m_commands;
    };
}