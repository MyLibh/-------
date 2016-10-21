#include "Variables.hpp"
#include "vec.hpp"
#include "ProgramManager.hpp"

#define __DEBUG

#pragma comment (lib, "gdiplus.lib")
        
WCHAR     title_[MAX_LOADSTRING];         //        
WCHAR     wndClassName_[MAX_LOADSTRING];  // Внести в ProgramManager
ProgramManager programManager;

using namespace Gdiplus;

enum EXITS
{
	WNDCLASS_FAILED  = -15001,
	WNDCREATE_FAILED = -15002,

	ESCAPE           = 27,

	BALLS_STOPPED    =  15001
};

ATOM                MyRegisterClass();
HWND                InitInstance(INT);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND                EnableConsole();
VOID                DoFrame(HWND, Gdiplus::Graphics*, HDC, HBITMAP, HBITMAP);

INT APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     INT       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef __DEBUG 
	if(!EnableConsole()) cout << "Cannot alloc console" << endl; //Проблема с открытием!!! 
#endif

	GdiplusStartupInput gfd;
	ULONG_PTR token = NULL;
	Status st = GdiplusStartup(&token, &gfd, NULL);
    if (st != NULL) MessageBox(NULL, L"", L"FATAL ERROR", MB_OK | MB_ICONERROR);

	programManager.setHINSTANCE(hInstance);
	programManager.loadTitle(title_);
	programManager.loadWndClassName(wndClassName_);

    if(!MyRegisterClass()) return EXITS::WNDCLASS_FAILED;

	HWND hWnd = nullptr;
    if (!(hWnd = InitInstance(nCmdShow))) return EXITS::WNDCREATE_FAILED;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BILLIARDS));

    MSG msg = { };

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
	
		if(GetAsyncKeyState(27)) return EXITS::ESCAPE;
    }

	GdiplusShutdown(token);

#ifdef __DEBUG 
	PAUSE
#endif
    return static_cast<INT>(msg.wParam);
}

ATOM MyRegisterClass()
{
	//HBITMAP background = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = programManager.getHINSTANCE();
    wcex.hIcon          = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_BILLIARDS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = /*(background)? CreatePatternBrush(background) : */reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BILLIARDS);
    wcex.lpszClassName  = wndClassName_;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND InitInstance(INT nCmdShow)
{
   HWND hWnd = CreateWindowW(wndClassName_, title_, WS_OVERLAPPEDWINDOW,
      100, 100, programManager.getMemDCWindow().width, programManager.getMemDCWindow().height, nullptr, nullptr, programManager.getHINSTANCE(), nullptr);

   programManager.setHWND(hWnd);

   return hWnd;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd, NULL, 60, NULL);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            switch (wmId)
            {
            case IDM_ABOUT:
				DialogBox(programManager.getHINSTANCE(), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_MOUSEMOVE:      
		programManager.setCuePosition(lParam); 
		break;
	case WM_SIZE:
		{
			RECT tmpRect = {};
			GetClientRect(hWnd, &tmpRect); 

			programManager.setMemDCWindow(tmpRect);
		}
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, false);
		break;
    case WM_PAINT:
		{
			programManager.dump();

            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);

			programManager.initDubbleBuffering(hDC);
			PatBlt(programManager.getMemDC(), 0, 0, programManager.getMemDCWindow().width, programManager.getMemDCWindow().height, WHITENESS);
			
			programManager.moveBalls();
			programManager.moveCue();
			
			programManager.drawTable();
			programManager.drawBalls();
			programManager.drawCue();
			                               
			if(programManager.stopBalls()) PostQuitMessage(EXITS::BALLS_STOPPED); 
 	
			programManager.loadBufferIntoCanvas(hDC);
			programManager.clearDubbleBuffering();
			
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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

		std::ios::sync_with_stdio();
	}
	
	HWND console = GetConsoleWindow();
	SetWindowPos(console, NULL, 0, 0, 700, 500, SWP_NOSIZE | SWP_NOZORDER);

	return console;
}
