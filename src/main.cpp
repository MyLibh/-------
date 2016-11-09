#include "ProgramManager.hpp"
#include "Player.hpp"

#include <WinSock.h>
#include <iostream>
//#include <WS2tcpip.h>

#define __DEBUG

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Wsock32.lib")

using namespace Gdiplus;    

ProgramManager *programManager = nullptr;
Player player1(TRUE, L"Алексий");
Player player2(FALSE);
GameInfo gameInfo;

ATOM                MyRegisterClass(HINSTANCE, WCHAR[]);
HWND                InitInstance(HINSTANCE, INT, WCHAR[], WCHAR[]);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND                EnableConsole();

CONST SIZE_T MAX_LOADSTRING = 64;

INT APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     INT       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//system("chcp 1251");

#ifdef __DEBUG 
	if(!EnableConsole()) return EXITS::CONSOLECREATE_FAILED;
#endif

	GdiplusStartupInput gfd;
	ULONG_PTR token = NULL;
	Status st = GdiplusStartup(&token, &gfd, NULL);
	if (st != NULL) return EXITS::GDIPINIT_FAILED;

	WCHAR title[MAX_LOADSTRING] = L"";
	WCHAR wndClassName[MAX_LOADSTRING] = L"";

	LoadStringW(hInstance, IDS_APP_TITLE, title, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BILLIARDS, wndClassName, MAX_LOADSTRING);

	if (!MyRegisterClass(hInstance, wndClassName)) return EXITS::WNDCLASS_FAILED;

	HWND hWnd = nullptr;
	if (!(hWnd = InitInstance(hInstance, nCmdShow, title, wndClassName))) return EXITS::WNDCREATE_FAILED;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	programManager = new ProgramManager(hWnd, hInstance);

	Config config;

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BILLIARDS));
	MSG msg = { };

	srand(static_cast<unsigned>(time(NULL)));

	/*
	//=======================================================================================
	
	SOCKET server;
	WSADATA wsData;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsData))) return E_FAIL;
	
	if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return E_FAIL;

	sockaddr_in s_addrs;
	ZeroMemory(&s_addrs, sizeof (s_addrs));

	s_addrs.sin_family = AF_INET;
	s_addrs.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
	s_addrs.sin_port = htons(1234);

	if (connect(server, reinterpret_cast<sockaddr*>(&s_addrs), sizeof(s_addrs)) == SOCKET_ERROR) return E_FAIL;
   
	char buff[512] = "HELLO WORLD";
	if (send(server, buff, 512, 0) == SOCKET_ERROR)  return E_FAIL;
	
	if (FAILED(recv(server, buff, 512, 0))) return E_FAIL;

	CONST WORD LENGTH = 128;
	char ip[LENGTH] = "";
	char port[LENGTH / 4] = "";
	char num[16] = "";

	if (FAILED(recv(server, ip, LENGTH, 0))) return E_FAIL;
	if (FAILED(recv(server, port, LENGTH / 4, 0))) return E_FAIL;
	if (FAILED(recv(server, num, 16, 0))) return E_FAIL;

	closesocket(server);
	//==================================

	char buff2[512] = "HELLO WORLD2";
	if (atoi(num) == 1) 
	{
		cout << "AMA HEAR";
		SOCKET player2socs;
		if ((player2socs = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return -1;

		sockaddr_in s_addrp2s;
		ZeroMemory(&s_addrp2s, sizeof(s_addrp2s));

		s_addrp2s.sin_family = AF_INET;
		s_addrp2s.sin_addr.S_un.S_addr = inet_addr(ip); 
		s_addrp2s.sin_port = htons(static_cast<u_short>(atoi(port)));
	
		if (connect(player2socs, reinterpret_cast<sockaddr*>(&s_addrp2s), sizeof(s_addrp2s)) == SOCKET_ERROR) return -2;
   
		if (send(player2socs, buff2, 512, 0) == SOCKET_ERROR)  return -3;
		closesocket(player2socs);
	}
	else 
	{
		cout << "AMA NOT HEAR";
		SOCKET player2socr;
		if ((player2socr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return -4;

		sockaddr_in s_addrp2r;
		ZeroMemory(&s_addrp2r, sizeof(s_addrp2r));

		s_addrp2r.sin_family			= PF_INET;
		s_addrp2r.sin_addr.S_un.S_addr	= htonl(INADDR_ANY);																
		s_addrp2r.sin_port				= htons(static_cast<u_short>(atoi(port)));

		if (bind(player2socr, reinterpret_cast<sockaddr*>(&s_addrp2r), sizeof(s_addrp2r)) == SOCKET_ERROR) return -5;
		if (FAILED(listen(player2socr, SOMAXCONN))) return -6;

		SOCKET player2socs;
		sockaddr_in player2socsaddr;

		ZeroMemory(&player2socsaddr, sizeof(player2socsaddr));
		int new_len = sizeof(player2socsaddr);

		if (FAILED(player2socs = accept(player2socr, (sockaddr*)&player2socsaddr, &new_len))) return -7;		
		else {if (FAILED(recv(player2socs, buff2, 512, 0))) return -8;}

		closesocket(player2socs);
		closesocket(player2socr);
		cout << buff2;		
	}

	
	//==============================================================================================
	*/

	gameInfo.turn = Turns::Blow;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
    {
		
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }		

		player1.turn(*programManager, gameInfo);
		player2.turn(*programManager, gameInfo);

		if(Key(27)) return EXITS::ESCAPE;
    }

	GdiplusShutdown(token);	
	delete(programManager);

#ifdef __DEBUG 
	PAUSE
#endif

    return static_cast<INT>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance, WCHAR wndClassName[])
{
    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_BILLIARDS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BILLIARDS);
    wcex.lpszClassName  = wndClassName;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND InitInstance(HINSTANCE hInstance, INT nCmdShow, WCHAR title[], WCHAR wndClassName[])
{
   HWND hWnd = CreateWindowW(wndClassName, title, WS_OVERLAPPEDWINDOW,
      0, 0, static_cast<INT>(sizeX), static_cast<INT>(sizeY) + 100, nullptr, nullptr, hInstance, nullptr);

   return hWnd;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		//SetTimer(hWnd, NULL, 1, NULL);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            switch (wmId)
            {
            case IDM_ABOUT:
				cout << DialogBox(programManager->getHINSTANCE(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About) << endl;
                break;
			case IDM_RESTART:
				gameInfo.restart();
				programManager->restart();
				player1.restart();
				player2.restart();
				break;
			case IDM_SAVE:
				//programManager->save();
				break;
            case IDM_EXIT:
				//programManager->~ProgramManager();
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_MOUSEMOVE:      
		programManager->setMouse(lParam, static_cast<INT16>(wParam)); 
		break;
	case WM_SIZE:
		{
			//RECT tmpRect = {};
			//GetClientRect(hWnd, &tmpRect); 

			//programManager.setMemDCWindow(tmpRect);
		}
		break;
	case WM_TIMER:
		//InvalidateRect(hWnd, NULL, false);
		break;
    case WM_PAINT:
		{
			programManager->onPAINT(); 
        }
        break;
    case WM_DESTROY:
		//programManager->~ProgramManager();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
	case WM_INITDIALOG:
        return static_cast<INT_PTR>(TRUE);

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

HWND EnableConsole()
{
	if(AllocConsole()) 
	{
		int hCrt = _open_osfhandle(reinterpret_cast<LONG>(GetStdHandle(STD_OUTPUT_HANDLE)), 4);
		if(!hCrt) return FALSE;
  
		*stdout = *_fdopen(hCrt, "w");
		setvbuf(stdout, NULL, _IONBF, 0);

		*stderr = *_fdopen(hCrt, "w");
		setvbuf(stderr, NULL, _IONBF, 0);

		ios::sync_with_stdio();
	}
	
	HWND console = GetConsoleWindow();
	SetWindowPos(console, NULL, 0, 0, 700, 500, SWP_NOSIZE | SWP_NOZORDER);

	return console;
}
