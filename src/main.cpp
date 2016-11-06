#include "ProgramManager.hpp"
#include "Player.hpp"

#define __DEBUG

#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;    

ProgramManager *programManager = nullptr;

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

	system("chcp 1251");

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

	srand(static_cast< unsigned >(time(NULL)));

	Player player1(TRUE, L"Алексий");
	Player player2(FALSE);
	GameInfo gameInfo; gameInfo.turn = Turns::Blow;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }		
		//$r programManager->dump();

		player1.turn(*programManager, gameInfo);
		player2.turn(*programManager, gameInfo);

		//cout << gameInfo.firstScore << endl;

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
      0, 0, static_cast<INT>(sizeX) + 100, static_cast<INT>(sizeY) + 100, nullptr, nullptr, hInstance, nullptr);

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
				//DialogBox(programManager->getHINSTANCE(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		programManager->setMouse(lParam, wParam); 
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
