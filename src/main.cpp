#include "ProgramManager.hpp"

#define __DEBUG

#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;      

WCHAR     title_[MAX_LOADSTRING];         //        
WCHAR     wndClassName_[MAX_LOADSTRING];  // ¬нести в ProgramManager
ProgramManager programManager;
Image *background;
Image *table;
Image *ball0;
Image *ball1;
Image *ball2;
Image *ball3;
Image *ball4;
Image *ball5;
Image *ball6;
Image *ball7;
Image *ball8;
Image *ball9;
Image *ball10;
Image *ball11;
Image *ball12;
Image *ball13;
Image *ball14;
Image *ball15;
Image *cue;

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
	if(!EnableConsole()) return EXITS::CONSOLECREATE_FAILED;
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

	background = new Image(L"../src/Images/Background.jpg");
	table = new Image(L"../src/Images/Table.jpg");
	ball0 = new Image(L"../src/Images/0.png");
	ball1 = new Image(L"../src/Images/1.png");
	ball2 = new Image(L"../src/Images/2.png");
	ball3 = new Image(L"../src/Images/3.png");
	ball4 = new Image(L"../src/Images/4.png");
	ball5 = new Image(L"../src/Images/5.png");
	ball6 = new Image(L"../src/Images/6.png");
	ball7 = new Image(L"../src/Images/7.png");
	ball8 = new Image(L"../src/Images/8.png");
	ball9 = new Image(L"../src/Images/9.png");
	ball10 = new Image(L"../src/Images/10.png");
	ball11 = new Image(L"../src/Images/11.png");
	ball12 = new Image(L"../src/Images/12.png");
	ball13 = new Image(L"../src/Images/13.png");
	ball14 = new Image(L"../src/Images/14.png");
	ball15 = new Image(L"../src/Images/15.png");
	cue = new Image(L"../src/Images/Cue.png");
	
	//for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
	//{
	//	WCHAR wstr[MAX_LOADSTRING] = L"";
	//	swprintf(wstr, L"../src/Images/%d.jpg", 8);
	//}
	//programManager.initManager();

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

	delete(background);
	delete(table);
	delete ball0;
	delete ball1;
	delete ball2;
	delete ball3;
	delete ball4;
	delete ball5;
	delete ball6;
	delete ball7;
	delete ball8;	
	delete ball9;
	delete ball10;
	delete ball11;
	delete ball12;
	delete ball13;
	delete ball14;
	delete ball15;
	delete cue;

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
				DialogBox(programManager.getHINSTANCE(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		programManager.setLParam(lParam); 
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
			//$r programManager.dump();

            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);

			programManager.initDubbleBuffering(hDC); 
			programManager.loadBackgroundIntoCanvas(hDC, background);
			//PatBlt(programManager.getMemDC(), 0, 0, programManager.getMemDCWindow().width, programManager.getMemDCWindow().height, WHITENESS);
			
			programManager.moveBalls();
			programManager.moveCue();
			
			programManager.drawTable();
			programManager.drawBalls(ball0, 0);
		    programManager.drawBalls(ball1, 1);
			programManager.drawBalls(ball2, 2);
			programManager.drawBalls(ball3, 3);
			programManager.drawBalls(ball4, 4);
			programManager.drawBalls(ball5, 5);
			programManager.drawBalls(ball6, 6);
			programManager.drawBalls(ball7, 7);
			programManager.drawBalls(ball8, 8);
			programManager.drawBalls(ball9, 9);
			programManager.drawBalls(ball10, 10);
			programManager.drawBalls(ball11, 11);
			programManager.drawBalls(ball12, 12);
			programManager.drawBalls(ball13, 13);
			programManager.drawBalls(ball14, 14);
			programManager.drawBalls(ball15, 15);			
			programManager.drawCue(cue);
			                               
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
