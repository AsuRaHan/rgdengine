#pragma once

#include <rgde/input/base.h>

namespace input
{
    //������� (������, ��� � �.�.) ���������� �����
    class Control
    {
    public:        
        //���� ���������
        enum EType
        {
            Button,
            Axis
        };

        Control(types::control name, EType type, device_dx9 &device);

        types::control get_name () const {return m_name;}
		EType    getType () const {return m_type;}

        //�������� �����������
        void bind (CommandPtr command);
        void bind (const std::wstring &command_name);

        //������� �����������
        void unbind (CommandPtr command);
        void unbind (const std::wstring &command_name);

        //�������� �� ����� �����������
        bool isbind (CommandPtr command);
        bool isbind (const std::wstring &command_name);

        //��������� ������������ � ����� ���������
        void notifyAllObservers (); 

		bool getPress() const {return m_press;}

        int  m_time;
        bool m_press;
        int  m_delta;

    private:
        device_dx9          &m_device; //����������, �������� ����������� �������
        EType            m_type;   //��� ��������
        types::control  m_name;   //'���' ��������

		typedef std::list<CommandPtr> CommandsList;
		typedef CommandsList::iterator CommandsIter;

		//�������, � ������� �������� �������
        CommandsList m_commands;
    };
}