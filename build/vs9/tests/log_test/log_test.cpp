#include "stdafx.h"

#include <rgde/log/log.h>

#include <windows.h>
#include <boost/filesystem.hpp>

int _tmain(int argc, _TCHAR* argv[])
{	
	wchar_t buf[512];
	GetModuleFileNameW(NULL, &buf[0], 512);

	boost::filesystem::wpath p(buf);
	std::wstring path = p.branch_path().string() + L"/../data/";
	SetCurrentDirectoryW(path.c_str());


    using namespace rgde::log;

    logsystem log; //���� ���������� ��������� ������ logsystem ��� ��������

    lmsg << "(lmsg) ��������� � ���: " << 1 << std::endl;
    lwrn << "(lwrn) �������������� � ���: " << 2 << std::endl;
    lerr << "(lerr) ������ � ���: " << 3 << std::endl;

    lmsg << L"(wlmsg) ��������� � ���: " << 4 << std::endl;
    lwrn << L"(wlwrn) �������������� � ���: " << 5 << std::endl;
    lerr << L"(wlerr) ������ � ���: " << 6 << std::endl;

    std::cout << "(cout) ��������� � ���: " << 7 << std::endl;
    std::wcout << L"(wcout) ��������� � ���: " << 8 << std::endl;

    std::cerr << "(cerr) ������ � ���: " << 9 << std::endl;
    std::wcerr << L"(wcerr) ������ � ���: " << 10 << std::endl;

	return 0;
}

