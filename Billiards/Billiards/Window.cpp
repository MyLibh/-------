#include "stdafx.h"
#include "Resource.h"
#include "Window.hpp"

namespace Billiards
{
	Window::Window(LPCTSTR className, DWORD style, DWORD exstyle, LPCTSTR title, HINSTANCE hInstance, CONST WindowRect &crRect) :
		BaseWindow(className, style, exstyle, title, nullptr, nullptr, hInstance, crRect), 
		window_(crRect)
	{ }

	LRESULT Window::onCommand(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		INT wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst_, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd_, about);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd_);
			break;
		default:
			return onMessageDefault(msg, wParam, lParam);
		}
		return 0;
	}

	INT_PTR CALLBACK Window::about(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);

		switch (message)
		{
		case WM_INITDIALOG: return static_cast<INT_PTR>(TRUE);

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return static_cast<INT_PTR>(TRUE);
			}
			break;
		}
		return static_cast<INT_PTR>(FALSE);
	}

	ATOM registerClass(LPCTSTR className, HINSTANCE hInst)
	{
		WNDCLASSEX wcex = { sizeof(wcex) };

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= Window::baseWndProc;
		wcex.hInstance		= hInst;
		wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_BILLIARDS));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BILLIARDS);
		wcex.lpszClassName	= className;
		wcex.hIconSm		= LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassEx(&wcex);
	}

	MainLoopParameters::MainLoopParameters(HINSTANCE hInstance, CONST WindowRect &crRect) 
	{
		loadStrings(hInstance);
		registerClass(className, hInstance);
		
		pWindow = new Window(className, WS_OVERLAPPEDWINDOW, NULL, title, hInstance, crRect);
		pWindow->show();
	}

	MainLoopParameters::~MainLoopParameters() { delete(pWindow); }

	VOID MainLoopParameters::loadStrings(HINSTANCE hInstance)
	{
		static TCHAR szTitle[MAX_LOADSTRING] = L"";					
		static TCHAR szWindowClass[MAX_LOADSTRING] = L"";

		LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInstance, IDC_BILLIARDS, szWindowClass, MAX_LOADSTRING);

		title     = szTitle;
		className = szWindowClass;

		registerClass(className, hInstance);
	}

	INT MainLoop(LPMLFUNC func, MainLoopParameters *pParams)
	{
		MSG    msg         = {};
		HACCEL hAccelTable = LoadAccelerators(pParams->pWindow->getHINSTANCE(), MAKEINTRESOURCE(IDC_BILLIARDS));
		HWND   hWnd        = pParams->pWindow->getHWND();

	#pragma warning(push)
	#pragma warning(disable:4127) // Избежание warning'a в строке "while (TRUE)"
		while (TRUE)
		{
			if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
			{
				if(msg.message == 18) break;
				
			} else if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} 
			func(pParams->getWindow());
		}
	#pragma warning(pop)

		return static_cast<INT>(msg.wParam);
	}
}