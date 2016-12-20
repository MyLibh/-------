#include "stdafx.h"
#include "Model.hpp"
#include "Window.hpp"

Billiards::MLFUNC MainFunction(CONST Billiards::Window&);
ULONG_PTR         InitGdiplus();

INT APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
                       _In_opt_ HINSTANCE,
                       _In_     LPTSTR,
                       _In_     INT)
{
	ULONG_PTR token = InitGdiplus();
	
	WinApiWrapper::WindowRect rect = { 0, 0, 800, 600 };
	Billiards::MainLoopParameters mlp(hInstance, rect);

	INT result = Billiards::MainLoop(MainFunction, &mlp);

	Gdiplus::GdiplusShutdown(token);	

	return result;
}

Billiards::MLFUNC MainFunction(CONST Billiards::Window& crWindow)
{
	static Billiards::model::Model model(crWindow.getHWND(), UPOINT(crWindow.getWindowRect().cx, crWindow.getWindowRect().cy));
	model.doModel();
}

ULONG_PTR InitGdiplus()
{
	Gdiplus::GdiplusStartupInput gfd;
	ULONG_PTR token = NULL;

	Gdiplus::Status status = GdiplusStartup(&token, &gfd, NULL);
	if(status != NULL) throw "Не удалось инициализировать Gdiplus\n";

	return token;
}