#include "Variables.hpp"
#include "vec.hpp"
#include "Balls.hpp"
//#include "ProgramManager.hpp"

#define MAX_LOADSTRING 100
#define __DEBUG

#pragma comment (lib, "gdiplus.lib")
        
WCHAR     title_[MAX_LOADSTRING];         //        
WCHAR     wndClassName_[MAX_LOADSTRING];  // Внести в ProgramManager

using namespace Gdiplus;

struct ProgrammManager
{
private:
	HWND        hWnd_;
	HDC         memDC_;
	HBITMAP     memHbm_;
	HBITMAP     oldHbm_;
	HINSTANCE   hInstance_;
	Graphics   *graphics_;
	Pen        *pen_;
	Font       *font_;
	SolidBrush *brush_;
	Balls       balls_;

	//Так можно делать???
	VOID reInitGraphics() { delete(graphics_); graphics_ = new Graphics(memDC_); }
	VOID reInitPen(Color color = Color::Yellow, REAL width = 10) { delete(pen_); pen_ = new Pen(color, width); }
	VOID reInitFont(const WCHAR *font = L"Times New Roman", REAL size = 25, INT style = 0, Unit unit = Unit::UnitPoint) { delete(font_); font_ = new Font(font, size, style, unit); }
	VOID reInitBrush(Color color = Color::Black) { delete(brush_); brush_ = new SolidBrush(color); }

public:
	ProgrammManager() : 
		hWnd_(nullptr),
		memDC_(nullptr), 
		memHbm_(nullptr), 
		oldHbm_(nullptr),
		hInstance_(nullptr),
		graphics_(nullptr),
		pen_(nullptr)
	{
		//HDC hDC = GetDC(hWnd_);

		

		//ReleaseDC(hWnd_, hDC);
	}

	~ProgrammManager()
	{
		//delete(graphics_); //Исключение, когда есть
		//delete(pen_);
		//delete(font_);
		//delete(brush_);

		DeleteObject(memHbm_);
		DeleteObject(oldHbm_);

		DeleteDC(memDC_);
	
		hWnd_   = nullptr;
		memDC_  = nullptr;
		memHbm_ = nullptr;
		oldHbm_ = nullptr;
	}

	VOID dump() const { cout << "memDC: " << memDC_ << ", memHbm: " << memHbm_ << ", oldHbm: " << oldHbm_ << ", hInst: " << hInstance_ << endl
							 << "hWnd: " << hWnd_ << ", title: " << title_ << ", wndClassName: " << wndClassName_ << endl 
							 << "graphics: " << graphics_ << ", pen: " << pen_ << ", font: " << font_ << ", brush: " << brush_ << endl << endl; }

	HDC       getMemDC() const { return memDC_; }
	HBITMAP   getMemHbm() const { return memHbm_; }
	HBITMAP   getOldHbm() const { return oldHbm_; }
	HWND      getHWND() const { return hWnd_; }
	HINSTANCE getHINSTANCE() const { return hInstance_; }
	WCHAR     getTitle() const { return *title_; }
	WCHAR     getWndClassName() const { return *wndClassName_; }
	Color     getPenColor() const { Color *retColor = NULL; pen_->GetColor(retColor); return *retColor; }
	REAL      getPenWidth() const { return pen_->GetWidth(); }
	//Стандартные функции для шрифта

	VOID setMemDC(HDC hDC) { memDC_ = hDC; }
	VOID setMemHbm(HBITMAP memHbm) { memHbm_ = memHbm; }
	VOID setOldHbm(HBITMAP oldHbm) { oldHbm_ = oldHbm; }
	VOID setHWND(HWND hWnd) { hWnd_ = hWnd; }
	VOID setHINSTANCE(HINSTANCE hInstance) { hInstance_ = hInstance; }
	//VOID setPenColor(Color color) { pen_->SetColor(color); }
	//VOID setPenWidth(REAL width) { pen_->SetWidth(width); }

	VOID loadTitle() { LoadStringW(hInstance_, IDS_APP_TITLE, title_, MAX_LOADSTRING); }
	VOID loadWndClassName() {LoadStringW(hInstance_, IDC_BILLIARDS_DIALOG, wndClassName_, MAX_LOADSTRING);}
	VOID loadBufferIntoCanvas(HDC canvas) { BitBlt(canvas, 0, 0, WINDOWSIZE.width, WINDOWSIZE.height, memDC_, 0, 0, SRCCOPY); }

	VOID initDubbleBuffering(HDC hDC)
	{
		setMemDC(CreateCompatibleDC(hDC));
		setMemHbm(CreateCompatibleBitmap(GetDC(hWnd_), WINDOWSIZE.width, WINDOWSIZE.height));
		setOldHbm((HBITMAP)SelectObject(getMemDC(), getMemHbm()));	

		reInitGraphics();
		reInitPen();
		reInitFont();
		reInitBrush();
	}

	VOID clearDubbleBuffering()
	{
		SelectObject(getMemDC(), getOldHbm());
		DeleteObject(getMemHbm());
		DeleteDC(getMemDC());
	}

	VOID drawTable()
	{
		graphics_->DrawLine(pen_, Point(static_cast<INT>(sizeX - sizestenaRIGHT), static_cast<INT>(sizestenaUP + Ru + RDugLuz)), Point(static_cast<INT>(sizeX - sizestenaRIGHT), static_cast<INT>(sizestenaUP + sizeYpol - Ru - RDugLuz)));
		graphics_->DrawLine(pen_, Point(static_cast<INT>(        sizestenaLEFT ), static_cast<INT>(sizestenaUP + Ru + RDugLuz)), Point(static_cast<INT>(        sizestenaLEFT ), static_cast<INT>(sizestenaUP + sizeYpol - Ru - RDugLuz)));

		graphics_->DrawLine(pen_, Point(static_cast<INT>(sizestenaLEFT +            (Ru + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)));
		graphics_->DrawLine(pen_, Point(static_cast<INT>(sizestenaLEFT + sizeXpol - (Ru + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)));

		graphics_->DrawLine(pen_, Point(static_cast<INT>(sizestenaLEFT +            (Ru + RDugLuz)), static_cast<INT>(sizestenaUP)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz)), static_cast<INT>(sizestenaUP)));
		graphics_->DrawLine(pen_, Point(static_cast<INT>(sizestenaLEFT + sizeXpol - (Ru + RDugLuz)), static_cast<INT>(sizestenaUP)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)), static_cast<INT>(sizestenaUP)));

	
		graphics_->DrawEllipse(pen_, static_cast<INT>(        sizestenaLEFT  - RDugLuz - (RLuz + 1) / 2), static_cast<INT>(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
		graphics_->DrawEllipse(pen_, static_cast<INT>(sizeX - sizestenaRIGHT + RDugLuz - (RLuz + 1) / 2), static_cast<INT>(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
		graphics_->DrawEllipse(pen_, static_cast<INT>(sizeX - sizestenaRIGHT + RDugLuz - (RLuz + 1) / 2), static_cast<INT>(        sizestenaUP   - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
		graphics_->DrawEllipse(pen_, static_cast<INT>(        sizestenaLEFT  - RDugLuz - (RLuz + 1) / 2), static_cast<INT>(        sizestenaUP   - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);

		graphics_->DrawEllipse(pen_, static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + 1) / 2), static_cast<INT>(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
		graphics_->DrawEllipse(pen_, static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + 1) / 2), static_cast<INT>(        sizestenaUP   - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);

		for (int i = 0; i < ColvoCenterDugLuz; i++) graphics_->DrawEllipse(pen_, static_cast<INT>(CenterDugLuz[i].x - RDugLuz  / 2), static_cast<INT>(CenterDugLuz[i].y - RDugLuz / 2), RDugLuz, RDugLuz);
	}

	VOID drawBalls() { balls_.draw(graphics_, pen_, font_, brush_); }
	VOID moveBalls() { balls_.move(); }
	BOOL stopBalls() { if(balls_.stopped()) graphics_->DrawString(L"EZ WIN", strlen("EZ WIN"), font_, PointF(10, 10), brush_); return balls_.stopped(); }
} programManager;

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
	programManager.loadTitle();
	programManager.loadWndClassName();

    MyRegisterClass();

	HWND hWnd = nullptr;
    if (!(hWnd = InitInstance(nCmdShow))) return FALSE;
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

ATOM MyRegisterClass()
{
	//HBITMAP background = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = programManager.getHINSTANCE();
    wcex.hIcon          = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_GDI_));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = /*(background)? CreatePatternBrush(background) : */reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BIG);
    wcex.lpszClassName  = wndClassName_;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND InitInstance(INT nCmdShow)
{
   HWND hWnd = CreateWindowW(wndClassName_, title_, WS_OVERLAPPEDWINDOW,
      100, 100, WINDOWSIZE.width, WINDOWSIZE.height, nullptr, nullptr, programManager.getHINSTANCE(), nullptr);

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
	case WM_SIZE:
		{
			//RECT tmpRect = {};
			//GetClientRect(hWnd, &tmpRect); // Поставить, чтобы после reSize() memDC.size() менялось

			//WINDOWSIZE = tmpRect;
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

			//Graphics *grap = new Graphics(hDC);			
			//grap->RotateTransform(10);
			//grap->DrawImage(new Image(L"../src/Images/8.jpg"), RectF(100, 100, static_cast<REAL>(WINDOWSIZE.width)/5, static_cast<REAL>(WINDOWSIZE.height)/5));
			//delete(grap);

			programManager.initDubbleBuffering(hDC);
			PatBlt(programManager.getMemDC(), 0, 0, WINDOWSIZE.width, WINDOWSIZE.height, WHITENESS);
			
			programManager.moveBalls();
			programManager.drawTable();
			programManager.drawBalls();
			                               
			if(programManager.stopBalls()) { system("pause"); PostQuitMessage(1); }
 	
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
