#include "ProgramManager.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

ProgramManager::ProgramManager(HWND hWnd, HINSTANCE hInstance) : 
	window_(static_cast<SIZE_T>(sizeX + 100), static_cast<SIZE_T>(sizeY + 100)),
	hWnd_(hWnd),
	memDC_(nullptr), 
	memHbm_(nullptr), 
	oldHbm_(nullptr),
	hInstance_(hInstance),
	textures_(new Textures()),
	exit_(Rect(static_cast<INT>(sizeX), 0, 100, 100), TEXTS[Menu::ButtonTextsId::EXIT], TRUE),
	graphics_(nullptr),
	pen_(new Pen(Color::Yellow, 10)),
	font_(new Font(L"Times New Roman", 25, 0, Unit::UnitPoint)),
	brush_(new SolidBrush(Color::Black))	
{
	LoadStringW(hInstance_, IDS_APP_TITLE, title_, MAX_LOADSTRING);
	LoadStringW(hInstance_, IDC_BILLIARDS, wndClassName_, MAX_LOADSTRING);

	anotherPlayerText_ = L"ÊÎÌÏÓÊÒÅÐ: 0";
	anotherPlayerPoint_ = PointF(0, 100);
	anotherPlayerColor_ = Color::Red; 
}

ProgramManager::~ProgramManager()
{
	delete(graphics_); 
	delete(pen_);
	delete(font_);
	delete(brush_);

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

	for (int i = 0; i < ColvoCenterDugLuz; i++) graphics_->DrawEllipse(pen_, static_cast<INT>(CenterDugLuz[i].getX() - RDugLuz  / 2), static_cast<INT>(CenterDugLuz[i].getY() - RDugLuz / 2), RDugLuz, RDugLuz);
}

VOID ProgramManager::initDubbleBuffering(HDC hDC)
{
	setMemDC(CreateCompatibleDC(hDC));
	setMemHbm(CreateCompatibleBitmap(GetDC(hWnd_), window_.width, window_.height));
	setOldHbm((HBITMAP)SelectObject(getMemDC(), getMemHbm()));	
	setDefaults();

	graphics_ = new Graphics(memDC_);
}

VOID ProgramManager::clearDubbleBuffering()
{
	SelectObject(getMemDC(), getOldHbm());
	DeleteObject(getMemHbm());
	DeleteDC(getMemDC());

	delete(graphics_);
}

VOID ProgramManager::setDefaults()
{
	setPenColor();
	setPenWidth();
	setBrushColor();
	//ôóíêöèè äëÿ øðèôòà
}

VOID ProgramManager::onPAINT()
{}

VOID ProgramManager::work(wstring text, PointF point /* = PointF(0, 0) */, Color color /* = Color::LightGreen */, BOOL drawCue /* = TRUE */)
{
    HDC hDC = GetDC(hWnd_);

	initDubbleBuffering(hDC); 
	loadBackgroundIntoCanvas(hDC);
			
	//mouse_.dump();
	//exit_.dump();

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

		setBrushColor(color);
		graphics_->DrawString(text.c_str(), text.length(), font_, point, brush_);
		setBrushColor(anotherPlayerColor_);
		graphics_->DrawString(anotherPlayerText_.c_str(), text.length(), font_, anotherPlayerPoint_, brush_);

		anotherPlayerText_  = text;
		anotherPlayerPoint_ = point;
		anotherPlayerColor_ = color; 

		if(exit_.pressed(Mouse::getCoords(), Mouse::getButton())) Menu::activate();

		moveBalls();
		if(drawCue) moveCue();
	}

	

	loadBufferIntoCanvas(hDC);	
	clearDubbleBuffering();
			
	ReleaseDC(hWnd_, hDC); 
}

//=============================================================

