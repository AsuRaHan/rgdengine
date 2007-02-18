#include "stdafx.h"
#include "zColumns.h"

#include "game.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	std::auto_ptr<core::IApplication> pApp(core::IApplication::Create(L"RGDE: zColumns Game", 400, 600, 32, 85, false));
	pApp->addTask(core::PTask(new core::CInputTask(*pApp, 0, false)));
	pApp->addTask(core::PTask(new core::CGameTask(*pApp, 1)));
	pApp->addTask(core::PTask(new core::CRenderTask(*pApp, 2)));

	{
		zcollumns::Game game;
		pApp->Run();
	}

	return 0;
}