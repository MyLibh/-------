#include "ProgramManager.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

ProgramManager::ProgramManager() : 
	hWnd_(nullptr),
	memDC_(nullptr), 
	memHbm_(nullptr), 
	oldHbm_(nullptr),
	hInstance_(nullptr),
	mouse_(),
	graphics_(nullptr),
	pen_(nullptr),
	font_(nullptr),
	brush_(nullptr),
	window_()
{
	window_.width  = static_cast<SIZE_T>(sizeX + 100); //static_cast<SIZE_T>(floor((DistanceBWAT.left + TABLE_SIZE.width  + DistanceBWAT.right ) * SCALE));
	window_.height = static_cast<SIZE_T>(sizeY + 100); //static_cast<SIZE_T>(floor((DistanceBWAT.up   + TABLE_SIZE.height + DistanceBWAT.bottom) * SCALE));

	//loadTextures();

	//HDC hDC = GetDC(hWnd_);
	//ReleaseDC(hWnd_, hDC);
}

ProgramManager::ProgramManager(CONST ProgramManager &manager)
{
}

ProgramManager::~ProgramManager()
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

VOID ProgramManager::drawTable(Image*)
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
}

VOID ProgramManager::initManager()
{
	reInitGraphics();
	reInitPen();
	reInitFont();
	reInitBrush();
}

VOID ProgramManager::onPAINT(Image *background, Image *table, Image *cue, Image *balls[])
{
	$r dump();

    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd_, &ps);

	initDubbleBuffering(hDC); 
	loadBackgroundIntoCanvas(hDC, background);
			
	moveBalls();
	moveCue();
			
	drawTable(table);
	drawBalls(balls);
	drawCue(cue);			                               
 	
	loadBufferIntoCanvas(hDC);
	clearDubbleBuffering();
			
	EndPaint(hWnd_, &ps);
}

//////////////////////////////////////////

VOID ProgramManager::onPAINT(Textures *textures)
{
	$r dump();

    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd_, &ps);

	initDubbleBuffering(hDC); 
	loadBackgroundIntoCanvas(hDC, textures->getBackgroundTexture());
			
	moveBalls();
	moveCue();
			
	drawTable(textures->getTableTexture());
	drawBalls(textures->balls_);
	drawCue(textures->getCueTexture());			                               
 	
	loadBufferIntoCanvas(hDC);
	clearDubbleBuffering();
			
	EndPaint(hWnd_, &ps);
}