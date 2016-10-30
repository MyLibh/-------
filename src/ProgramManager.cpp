#include "ProgramManager.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

ProgramManager::ProgramManager() : 
	window_(static_cast<SIZE_T>(sizeX + 100), static_cast<SIZE_T>(sizeY + 100)),
	hWnd_(nullptr),
	memDC_(nullptr), 
	memHbm_(nullptr), 
	oldHbm_(nullptr),
	hInstance_(nullptr),
	textures_(nullptr),
	exit_(Rect(static_cast<INT>(sizeX), 0, 100, 100), TEXTS[WTEXTS::Exit], TRUE),
	mouse_(),
	graphics_(nullptr),
	pen_(nullptr),
	font_(nullptr),
	brush_(nullptr)	
{
	LoadStringW(hInstance_, IDS_APP_TITLE, title_, MAX_LOADSTRING);
	LoadStringW(hInstance_, IDC_BILLIARDS, wndClassName_, MAX_LOADSTRING);
}

//ProgramManager::ProgramManager(ProgramManager &manager) { $b PAUSE; }

ProgramManager::~ProgramManager()
{
	//delete(graphics_); //Исключение, когда есть
	//delete(pen_);
	//delete(font_);
	//delete(brush_);

	delete(textures_);

	DeleteObject(memHbm_);
	DeleteObject(oldHbm_);

	DeleteDC(memDC_);
	
	hWnd_   = nullptr;
	memDC_  = nullptr;
	memHbm_ = nullptr;
	oldHbm_ = nullptr;
}

VOID ProgramManager::drawTable() const
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

	for (int i = 0; i < ColvoCenterDugLuz; i++) graphics_->DrawEllipse(pen_, static_cast<INT>(CenterDugLuz[i].getX() - RDugLuz  / 2), static_cast<INT>(CenterDugLuz[i].getY() - RDugLuz / 2), RDugLuz, RDugLuz);
}

VOID ProgramManager::clearDubbleBuffering()
{
	SelectObject(getMemDC(), getOldHbm());
	DeleteObject(getMemHbm());
	DeleteDC(getMemDC());
}

VOID ProgramManager::initDubbleBuffering(HDC hDC)
{
	setMemDC(CreateCompatibleDC(hDC));
	setMemHbm(CreateCompatibleBitmap(GetDC(hWnd_), window_.width, window_.height));
	setOldHbm((HBITMAP)SelectObject(getMemDC(), getMemHbm()));	

	reInitGraphics();
	reInitPen();
	reInitFont();
	reInitBrush();
	reInitTextures();
}

VOID ProgramManager::initManager()
{
	reInitGraphics();
	reInitPen();
	reInitFont();
	reInitBrush();
}

VOID ProgramManager::onPAINT()
{}

VOID ProgramManager::work()
{
    HDC hDC = GetDC(hWnd_);

	initDubbleBuffering(hDC); 
	loadBackgroundIntoCanvas(hDC);
			
	//mouse_.dump();
	//exit_.dump();

	if(menu_.isActive())
	{
		drawMenu();
		menu_.procedure(mouse_, &balls_);
	}
	else
	{
	drawTable();
	drawBalls();
	drawCue();	
	drawExit();

	if(exit_.pressed(mouse_)) menu_.activate();

	moveBalls();
	moveCue();
	}
 	
	loadBufferIntoCanvas(hDC);
	clearDubbleBuffering();
			
	ReleaseDC(hWnd_, hDC);
}