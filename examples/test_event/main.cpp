//main.cpp
//#include <event/event.h>
//#include <string>
//#include <iostream>

////-----------------------------------------------
//typedef event::TEvent<std::wstring> CSayEvent;
//
////-----------------------------------------------
//struct Named
//{
//    Named(std::wstring n): name(n) {};
//    std::wstring name;
//};
//
////-----------------------------------------------
////�����
//class CSpy: public event::CListener, public Named
//{
//public:
//    CSpy(std::wstring n): Named(n) {}
//
//    void spy(CSayEvent event)
//    {
//        std::wcout << name << L" ���������: " << event.m_data << std::endl;
//    }
//};
//
////�������
//class CMan: public event::CActor, public Named
//{
//public:
//    CMan(std::wstring n): Named(n) {}
//
//    void hear(CSayEvent event)
//    {
//        std::wcout << name << L" �������: " << event.m_data << std::endl;
//    }
//};
//
////�������
//class CWoman: public event::CActor, public Named
//{
//public:
//    CWoman(std::wstring n): Named(n) {}
//
//    void hear(CSayEvent event)
//    {
//        std::wcout << name << L" ��������: " << event.m_data << std::endl;
//    }
//};
//
////�������
//class CBaby: public event::CActor, public Named
//{
//public:
//    CBaby(std::wstring n): Named(n) {}
//};
//
////-----------------------------------------------
//class A: public event::CActor
//{
//public:
//    void f(const std::string &name, const std::string &param)
//    {
//        std::cout<<"Name: "<<name<<" Param: "<<param<<"\n";
//    }
//};
//
////-----------------------------------------------
void main()
{
    //std::wcout.imbue(std::locale(".866"));

    //{
    //    CSpy spy1(L"Bond"),
    //         spy2(L"Kazanova");

    //    CMan man1(L"Adam"),
    //         man2(L"Superman"),
    //         man3(L"Romeo");

    //    CWoman woman1(L"Eva"),
    //           woman2(L"Juliet"),
    //           woman3(L"Anna");

    //    CBaby baby1(L"Kain"),
    //          baby2(L"Avel");

    //    //���� ������������ ��� ���������
    //    spy1.subscribe<CSayEvent>(&spy1, &CSpy::spy);

    //    //�������� ������������ ������ ������
    //    spy2.subscribe<CSayEvent>(&spy2, &CSpy::spy, &woman1);
    //    spy2.subscribe<CSayEvent>(&spy2, &CSpy::spy, &woman2);
    //    spy2.subscribe<CSayEvent>(&spy2, &CSpy::spy, &woman3);

    //    //�������� ������ ���!
    //    man2.subscribe<CSayEvent>(&man2, &CMan::hear);

    //    //���� ������ ������ ���
    //    man1.subscribe<CSayEvent>(&man1, &CMan::hear, &woman1);

    //    //��� ������ ������ ����� � ����� �����
    //    woman1.subscribe<CSayEvent>(&woman1, &CWoman::hear, &man1);
    //    woman1.subscribe<CSayEvent>(&woman1, &CWoman::hear, &baby1);
    //    woman1.subscribe<CSayEvent>(&woman1, &CWoman::hear, &baby2);

    //    //��������� � ���� ���� � ������ �� ������
    //    //����� ����� � ��� �� ����� � ��������� � �� �������� �������� �������� �� ���������
    //    //����� ������� �����, ��� ������� ������

    //    //-----------------------------------
    //    //����� ��������� �� ���������
    //    man3.sendEvent(CSayEvent(L"� ���������! ����� �� ������, �? �� �� �� �����-��?"));
    //    std::wcout<<std::endl<<std::endl;

    //    //���� ������������
    //    man1.sendEvent(CSayEvent(L"����! ���� �����!"));
    //    std::wcout<<std::endl<<std::endl;

    //    //���� �� ��� ������� � ����
    //    woman3.sendEvent(CSayEvent(L"�� ���� ���������� ��� �����������?"));
    //    std::wcout<<std::endl<<std::endl;

    //    //���� �������
    //    baby2.sendEvent(CSayEvent(L"����! � ���� ���� �������!"));
    //    std::wcout<<std::endl<<std::endl;
    //}

    //{
    //    A a1,a2,a3;

    //    a1.subscribe("SomeName1", &a1, &A::f);
    //    a2.subscribe("SomeName2", &a2, &A::f);

    //    a3.sendEvent("SomeName1","to a1");
    //    a3.sendEvent("SomeName2","to a2");
    //    a3.sendEvent("SomeName3","to nothing");
    //}

    //event::IEventManager::DeleteAllManagers();
}