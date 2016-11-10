#include "ProgramManager.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

ProgramManager::ProgramManager(HWND hWnd, HINSTANCE hInstance) : 
	hWnd_(hWnd),
	memDC_(nullptr), 
	memHbm_(nullptr), 
	oldHbm_(nullptr),
	hInstance_(hInstance),
	//title_(),
	//wndClassName_(),
	pGraphics_(nullptr),
	pPen_(new Pen(static_cast<ARGB>(Color::Yellow, 10))),
	pFont_(new Font(L"Times New Roman", 25, 0, Unit::UnitPoint)),
	pBrush_(new SolidBrush(static_cast<ARGB>(Color::Black))),
	config_(),
	pTextures_(new Textures()),
	exit_(Rect(static_cast<INT>(sizeX), 0, 100, 100), TEXTS[Menu::ButtonTextsId::EXIT], TRUE),
	window_(static_cast<SIZE_T>(sizeX), static_cast<SIZE_T>(sizeY)),
	anotherPlayerText_(L" ŒÃœ” “≈–: 0"),
	anotherPlayerPoint_(PointF(static_cast<REAL>(sizeX), 0)),
	anotherPlayerColor_(static_cast<ARGB>(Color::Red))
{
	LoadStringW(hInstance_, IDS_APP_TITLE, title_, MAX_LOADSTRING);
	LoadStringW(hInstance_, IDC_BILLIARDS, wndClassName_, MAX_LOADSTRING);

	HDC hDC = GetDC(hWnd_);

	setMemDC(CreateCompatibleDC(hDC));
	setMemHbm(CreateCompatibleBitmap(hDC, window_.width, window_.height));
	setOldHbm(static_cast<HBITMAP>(SelectObject(memDC_, memHbm_)));	
	pGraphics_ = new Graphics(memDC_);

	ReleaseDC(hWnd_, hDC);
}

ProgramManager::~ProgramManager()
{
    $r cout << __FUNCTION__ << endl; 

	delete(pGraphics_); 
	delete(pPen_);
	delete(pFont_);
	delete(pBrush_);
	
	DeleteObject(memHbm_);
	DeleteObject(oldHbm_);

	DeleteDC(memDC_);
	
	hWnd_      = nullptr;
	hInstance_ = nullptr;
	memDC_     = nullptr;
	memHbm_    = nullptr;
	oldHbm_    = nullptr;
}

VOID ProgramManager::drawTable() const
{
	//ImageAttributes imAttr;
	//imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);
	//graphics_->DrawImage(&textures_->getTableTexture(), RectF(0, 0, static_cast<REAL>(sizeX), static_cast<REAL>(sizeY)), 0, 0, sizeX, sizeY, Unit::UnitPixel, &imAttr, 0); 

	pGraphics_->DrawLine(pPen_, Point(static_cast<INT>(sizeX - sizestenaRIGHT), static_cast<INT>(sizestenaUP + Ru + RDugLuz)), Point(static_cast<INT>(sizeX - sizestenaRIGHT), static_cast<INT>(sizestenaUP + sizeYpol - Ru - RDugLuz)));
	pGraphics_->DrawLine(pPen_, Point(static_cast<INT>(        sizestenaLEFT ), static_cast<INT>(sizestenaUP + Ru + RDugLuz)), Point(static_cast<INT>(        sizestenaLEFT ), static_cast<INT>(sizestenaUP + sizeYpol - Ru - RDugLuz)));

	pGraphics_->DrawLine(pPen_, Point(static_cast<INT>(sizestenaLEFT +            (Ru + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)));
	pGraphics_->DrawLine(pPen_, Point(static_cast<INT>(sizestenaLEFT + sizeXpol - (Ru + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)), static_cast<INT>(sizeY - sizestenaDOWN)));

	pGraphics_->DrawLine(pPen_, Point(static_cast<INT>(sizestenaLEFT +            (Ru + RDugLuz)), static_cast<INT>(sizestenaUP)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz)), static_cast<INT>(sizestenaUP)));
	pGraphics_->DrawLine(pPen_, Point(static_cast<INT>(sizestenaLEFT + sizeXpol - (Ru + RDugLuz)), static_cast<INT>(sizestenaUP)), Point(static_cast<INT>(sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)), static_cast<INT>(sizestenaUP)));

	pGraphics_->DrawEllipse(pPen_, static_cast<INT>(        sizestenaLEFT  - RDugLuz - (RLuz + 1) / 2), static_cast<INT>(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
	pGraphics_->DrawEllipse(pPen_, static_cast<INT>(sizeX - sizestenaRIGHT + RDugLuz - (RLuz + 1) / 2), static_cast<INT>(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
	pGraphics_->DrawEllipse(pPen_, static_cast<INT>(sizeX - sizestenaRIGHT + RDugLuz - (RLuz + 1) / 2), static_cast<INT>(        sizestenaUP   - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
	pGraphics_->DrawEllipse(pPen_, static_cast<INT>(        sizestenaLEFT  - RDugLuz - (RLuz + 1) / 2), static_cast<INT>(        sizestenaUP   - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);

	pGraphics_->DrawEllipse(pPen_, static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + 1) / 2), static_cast<INT>(sizeY - sizestenaDOWN + RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);
	pGraphics_->DrawEllipse(pPen_, static_cast<INT>(sizestenaLEFT + sizeXpol / 2 - (RLuz + 1) / 2), static_cast<INT>(        sizestenaUP   - RDugLuz - (RLuz + 1) / 2), RLuz + 1, RLuz + 1);

	for (int i = 0; i < ColvoCenterDugLuz; i++) pGraphics_->DrawEllipse(pPen_, static_cast<INT>(CenterDugLuz[i].getX() - RDugLuz  / 2), static_cast<INT>(CenterDugLuz[i].getY() - RDugLuz / 2), RDugLuz, RDugLuz);
}

VOID ProgramManager::initDubbleBuffering(HDC hDC)
{
	hDC;
	//setMemDC(CreateCompatibleDC(hDC));
	//setMemHbm(CreateCompatibleBitmap(hDC, window_.width, window_.height));
	//setOldHbm(static_cast<HBITMAP>(SelectObject(memDC_, memHbm_)));	
	setDefaults();

	//pGraphics_ = new Graphics(memDC_);
}

VOID ProgramManager::clearDubbleBuffering()
{
	//SelectObject(getMemDC(), getOldHbm());
	//DeleteObject(getMemHbm());
	//DeleteDC(getMemDC());
	PatBlt(memDC_, 0, 0, window_.width, window_.height, WHITENESS);
	//delete(pGraphics_);
}

VOID ProgramManager::setDefaults()
{
	setPenColor();
	setPenWidth();
	setBrushColor();
	//ÙÛÌÍˆËË ‰Îˇ ¯ËÙÚ‡
}

VOID ProgramManager::onPAINT()
{}

VOID ProgramManager::work(CONST wstring &rWext, CONST PointF &rPointf /* = PointF(0, 0) */, CONST Color &rColor /* = Color::LightGreen */, BOOL drawCue /* = TRUE */)
{
    HDC hDC = GetDC(hWnd_);

	initDubbleBuffering(hDC); 
	loadBackgroundIntoCanvas();

	if(Menu::isActive())
	{
		drawMenu();
		switch(menuProcedure(Mouse::getCoords(), Mouse::getButton()))
		{
		case MenuActions::Nothing:
			break;
		case MenuActions::Continue:
			Menu::deactivate();
			break;
		case MenuActions::Restart:
			Menu::deactivate();
			Balls::restart();
		case MenuActions::Help:
			//Help
			break;
		case MenuActions::Settings:
			//Settings
			break;
		case MenuActions::Profile:
			//Profile
			break;

		default: PostQuitMessage(EXITS::NONEBUTTON_PRESSED);
		}
	}
	else
	{
		drawTable();
		drawBalls();
		if(drawCue) this->drawCue();	
		drawExit();

		setBrushColor(rColor);
		pGraphics_->DrawString(rWext.c_str(), rWext.length(), pFont_, rPointf, pBrush_);
		setBrushColor(anotherPlayerColor_);
		pGraphics_->DrawString(anotherPlayerText_.c_str(), anotherPlayerText_.length(), pFont_, anotherPlayerPoint_, pBrush_);

		anotherPlayerText_  = rWext;
		anotherPlayerPoint_ = rPointf;
		anotherPlayerColor_ = rColor; 

		if(exit_.pressed(Mouse::getCoords(), Mouse::getButton())) Menu::activate();

		moveBalls();
		if(drawCue) moveCue();
	}

	loadBufferIntoCanvas(hDC);	
	clearDubbleBuffering();
			
	ReleaseDC(hWnd_, hDC); 
}

