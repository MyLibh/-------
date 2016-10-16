#include "Variables.hpp"
#include "vec.hpp"
#include "Balls.hpp"
#include "ProgramManager.hpp"

#define MAX_LOADSTRING 100
#define __DEBUG

#pragma comment (lib, "gdiplus.lib")


HINSTANCE hInst;                              
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];            
Balls balls;

ATOM                MyRegisterClass(HINSTANCE);
HWND                InitInstance(HINSTANCE, INT);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND                EnableConsole();
VOID                DoFrame(HWND, Gdiplus::Graphics*, HDC, HBITMAP, HBITMAP);

using namespace Gdiplus;

INT APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     INT       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	if(!EnableConsole()) cout << "Cannot alloc console" << endl; //Проблема с открытием!!!

	GdiplusStartupInput gfd;
	ULONG_PTR token = NULL;
	Status st = GdiplusStartup(&token, &gfd, NULL);
    if (st != NULL) MessageBoxA(NULL, "", "FATAL ERROR", MB_OK | MB_ICONERROR);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BILLIARDS_DIALOG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	HWND hWnd;
    if (!(hWnd = InitInstance (hInstance, nCmdShow))) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BIG));

    MSG msg = { };

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
	
		if(GetAsyncKeyState(27)) break;
    }

	GdiplusShutdown(token);

    return static_cast<INT>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//HBITMAP background = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDI_));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = /*(background)? CreatePatternBrush(background) : */reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BIG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND InitInstance(HINSTANCE hInstance, INT nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, WINDOWSIZE.width, WINDOWSIZE.height, nullptr, nullptr, hInstance, nullptr);

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
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, false);
		break;
    case WM_PAINT:
		{
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			HDC memDC = CreateCompatibleDC(hdc);
			HBITMAP memHbm = CreateCompatibleBitmap(GetDC(hWnd), WINDOWSIZE.width, WINDOWSIZE.height);
			HBITMAP oldHbm = (HBITMAP)SelectObject(memDC, memHbm);

			Graphics *graphics = new Graphics(memDC);
			Graphics *grap     = new Graphics(hdc);
			Pen *pen = new Pen(Color::Yellow, 10);
			SolidBrush *brush = new SolidBrush(Color::Black);
			//graphics->DrawLine(new Pen(Color::Red, 10), Point(10, 10), Point(100, 100));
			//graphics->DrawString(L"EZ WIN", strlen("EZ WIN"), new Font(L"Times New Roman", 25, 0, Unit::UnitPoint), PointF(10, 10), new SolidBrush(Color::Black));
            //graphics->DrawImage(new Image(L"../src/untitled.png"), RectF(50, 50, 1000, 1000)); 
			//graphics->DrawImage(new Image(L"../src/Images/Background.jpg"), RectF(0, 0, rect.right, rect.bottom));
			//graphics->DrawImage(new Image(L"Images/Background.jpg"), RectF(0, 0, 800, 457));
		
			PatBlt(memDC, 0, 0, WINDOWSIZE.width, WINDOWSIZE.height, WHITENESS);
			
			//grap->RotateTransform(10);
			//grap->DrawImage(new Image(L"../src/Images/8.jpg"), RectF(100, 100, static_cast<REAL>(WINDOWSIZE.width)/5, static_cast<REAL>(WINDOWSIZE.height)/5));

			graphics->DrawLine(pen, Point((int)(sizeX - sizestenaRIGHT), (int)(sizestenaUP + Ru + RDugLuz)), Point((int)(sizeX - sizestenaRIGHT), (int)(sizestenaUP + sizeYpol - Ru - RDugLuz)));
			graphics->DrawLine(pen, Point((int)sizestenaLEFT, (int)(sizestenaUP + (Ru + RDugLuz))), Point((int)sizestenaLEFT, (int)(sizestenaUP + sizeYpol - (Ru + RDugLuz))));
			graphics->DrawLine(pen, Point((int)(sizestenaLEFT +            (Ru + RDugLuz)), (int)(sizeY - sizestenaDOWN)), Point((int)(sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz)), (int)(sizeY - sizestenaDOWN)));
			graphics->DrawLine(pen, Point((int)(sizestenaLEFT + sizeXpol - (Ru + RDugLuz)), (int)(sizeY - sizestenaDOWN)), Point((int)(sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)), (int)(sizeY - sizestenaDOWN)));
			graphics->DrawLine(pen, Point((int)(sizestenaLEFT +            (Ru + RDugLuz)), (int)sizestenaUP), Point((int)(sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz)), (int)sizestenaUP));
			graphics->DrawLine(pen, Point((int)(sizestenaLEFT + sizeXpol - (Ru + RDugLuz)), (int)sizestenaUP), Point((int)(sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)), (int)sizestenaUP));

			graphics->DrawEllipse(pen, (int)(sizestenaLEFT - RDugLuz - (RLuz + 1) / 2), (int)(sizestenaUP - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
			graphics->DrawEllipse(pen, (int)(sizestenaLEFT - RDugLuz - (RLuz + 1) / 2), (int)(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
			graphics->DrawEllipse(pen, (int)(sizeX - sizestenaRIGHT + RDugLuz - (RLuz + 1) / 2), (int)(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
			graphics->DrawEllipse(pen, (int)(sizeX - sizestenaRIGHT + RDugLuz - (RLuz + 1) / 2), (int)(sizestenaUP - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
			graphics->DrawEllipse(pen, (int)(sizestenaLEFT + sizeXpol / 2 - (RLuz + 1) / 2), (int)(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
			graphics->DrawEllipse(pen, (int)(sizestenaLEFT + sizeXpol / 2 - (RLuz + 1) / 2), (int)(sizestenaUP - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);

			for (int i = 0; i < ColvoCenterDugLuz; i++) graphics->DrawEllipse(pen, (int)(CenterDugLuz[i].x - RDugLuz  / 2), (int)(CenterDugLuz[i].y - RDugLuz / 2), RDugLuz, RDugLuz);

			balls.move();                               
			balls.draw(graphics, pen, new Font(L"Times New Roman", 25, 0, Unit::UnitPoint), brush);
			if (balls.stopped()) graphics->DrawString(L"EZ WIN", strlen("EZ WIN"), new Font(L"Times New Roman", 25, 0, Unit::UnitPoint), PointF(10, 10), brush);
 	
			BitBlt(hdc, 0, 0, WINDOWSIZE.width, WINDOWSIZE.height, memDC, 0, 0, SRCCOPY);

			SelectObject(memDC, oldHbm);
			DeleteObject(memHbm);
			DeleteDC(memDC);

			delete(graphics);
			delete(grap);
			delete(pen);
			delete(brush);

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
