//device.h
#pragma once
#include "base.h"
#include <map>

namespace input
{

    //���������� �����
    class CDevice
    {
    public:
        CDevice(EDevice eName, int nIndx, CInputImpl &rInput):
            m_nIndx  (nIndx),
            m_eName  (eName),
            m_rInput (rInput)
        {
        }
        virtual ~CDevice();

        EDevice     getName () const {return m_eName;}  //�������� '���' ����������
        int         getIndx () const {return m_nIndx;}  //�������� ���������� ����� ����������
        CInputImpl& getInput()       {return m_rInput;} //�������� ���������� �����

        CControl* getControl       (EControl            eControlName);       //�������� �������
        CControl* getControl       (const std::wstring &sControlName);
        bool      isControlPresent (EControl            eControlName) const; //���� �� ����� �������
        bool      isControlPresent (const std::wstring &sControlName) const;

    protected:
        friend class CInputImpl;
        void addButton (EControl eControlName); //�������� ������
        void addAxis   (EControl eControlName); //�������� ���
        void detachCommand (PCommand pCommand); //�������� ������� ��� ���� ���������

        //->
        //init
        //getbuffereddata
        //process
        //-<

    private:
        int         m_nIndx;
        EDevice     m_eName;
        CInputImpl &m_rInput;

        std::map<EControl, CControl*> m_controls; //��������, ������� ���� � ����������
    };
}