#include "stdafx.h"
#include "Model.hpp"
#include "Window.hpp"

Billiards::MLFUNC         MainFunction(CONST Billiards::Window&);
WinApiWrapper::WindowRect InitWindowRect();
ULONG_PTR                 InitGdiplus();

template<typename TYPE>
inline TYPE MIN(TYPE a, TYPE b) { return (a > b)? a : b; }

//static Billiards::ScalingOptions scaleOptions(2, 2);

INT APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
                       _In_opt_ HINSTANCE,
                       _In_     LPTSTR,
                       _In_     INT)
{
	ULONG_PTR token = InitGdiplus();
	
	WinApiWrapper::InitConsole();

	Billiards::MainLoopParameters mlp(hInstance, InitWindowRect());
	
	INT result = Billiards::MainLoop(MainFunction, &mlp);
	
	Gdiplus::GdiplusShutdown(token);	

	return result;
}

Billiards::MLFUNC MainFunction(CONST Billiards::Window& crWindow)
{
	static Billiards::model::Model model(crWindow.getHWND(), UPOINT(crWindow.getWindowRect().cx, crWindow.getWindowRect().cy));
	model.doModel();
	std::cout << Billiards::scaleOptions.sx;
	Billiards::scaleOptions.sx = 2;
}

WinApiWrapper::WindowRect InitWindowRect()
{
	WinApiWrapper::WindowRect window = { };
	
	RECT rect = { };
	GetWindowRect(GetDesktopWindow(), &rect);

	//int min = MIN(rect.bottom, rect.right);
	//double size = (min == rect.bottom)? sizeX : sizeY;
	//short k = (size > min)? 1 : -1;

	Billiards::scaleOptions.sx = 2;

	/*for(; ; scaleOptions.sx += k)
		if(size / scaleOptions.sx <= min) break;

	if(k == 1)
	{
		rect.right *= scaleOptions.sx;
		rect.right *= scaleOptions.sx;
	}
	else 
	{
		rect.right /= scaleOptions.sx;
		rect.right /= scaleOptions.sx;
	}*/

	window.cx = rect.right;
	window.cy = rect.bottom;

	return window;
}

ULONG_PTR InitGdiplus()
{
	Gdiplus::GdiplusStartupInput gfd;
	ULONG_PTR token = NULL;

	Gdiplus::Status status = GdiplusStartup(&token, &gfd, NULL);
	if(status != NULL) throw "Не удалось инициализировать Gdiplus\n";

	return token;
}