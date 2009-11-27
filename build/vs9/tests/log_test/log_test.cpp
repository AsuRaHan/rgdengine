#include "stdafx.h"
#include <engine/log/log.h>

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace rgde::log;

    logsystem log; //���� ���������� ��������� ������ logsystem ��� ��������

    lmsg << "(lmsg) ��������� � ���: " << 1 << std::endl;
    lwrn << "(lwrn) �������������� � ���: " << 2 << std::endl;
    lerr << "(lerr) ������ � ���: " << 3 << std::endl;

    wlmsg << L"(wlmsg) ��������� � ���: " << 4 << std::endl;
    wlwrn << L"(wlwrn) �������������� � ���: " << 5 << std::endl;
    wlerr << L"(wlerr) ������ � ���: " << 6 << std::endl;

    std::cout << "(cout) ��������� � ���: " << 7 << std::endl;
    std::wcout << L"(wcout) ��������� � ���: " << 8 << std::endl;

    std::cerr << "(cerr) ������ � ���: " << 9 << std::endl;
    std::wcerr << L"(wcerr) ������ � ���: " << 10 << std::endl;

	return 0;
}

