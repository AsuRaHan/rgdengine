//control.h
#pragma once
#include "base.h"

namespace input
{

    //������� (������, ��� � �.�.) ���������� �����
    class CControl
    {
    public:
        
        //���� ���������
        enum EType
        {
            Button,
            Axis
        };

        CControl(EControl eName, EType eType, CDevice &rDevice);

        EControl getName () const {return m_eName;} //�������� '���' ��������
        EType    getType () const {return m_eType;} //�������� ��� ��������

        //�������� �����������
        void bind (PCommand pCommand);
        void bind (const std::wstring &sCommandName);

        //������� �����������
        void unbind (PCommand pCommand);
        void unbind (const std::wstring &sCommandName);

        //�������� �� ����� �����������
        bool isbind (PCommand pCommand);
        bool isbind (const std::wstring &sCommandName);

        //��������� ������������ � ����� ���������
        void notifyAllObservers (); 

        int  m_nTime;
        bool m_bPress;
        int  m_nDelta;

    private:
        CDevice            &m_rDevice;  //����������, �������� ����������� �������
        EType               m_eType;    //��� ��������
        EControl            m_eName;    //'���' ��������
        std::list<PCommand> m_commands; //�������, � ������� �������� �������
    };

}