#include "ProgramManager.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

ProgramManager::ProgramManager(HWND hWnd) :
	hWnd_(hWnd),
	hDC_(GetDC(hWnd_)),
	memDC_(NULL),
	memHbm_(NULL),
	oldHbm_(NULL),
	graphics_(new Graphics(memDC_)),
	font_(new Font(L"Times New Roman", 25, 0, Unit::UnitPoint)),
	brush_(new SolidBrush(Color::Black))
{ pen_ = new Pen(Color::Yellow, 10); }

ProgramManager::~ProgramManager()
{
	delete(graphics_);
	delete(pen_);
	delete(font_);
	delete(brush_);
	
	//HBITMAPÛ
	DeleteObject(memHbm_);
	DeleteObject(oldHbm_);

	DeleteDC(hDC_);
	DeleteDC(memDC_);
	
	hWnd_  = NULL;
	hDC_   = NULL;
	memDC_ = NULL;
}

VOID ProgramManager::drawTable()
{
	pen_->SetColor(Color::Yellow);
	pen_->SetWidth(10);

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

BOOL ProgramManager::drawAll()
{
	//PAINTSTRUCT pc;
	//HDC hDC = BeginPaint(hWnd_, &pc);

	//dump();

	//memDC_ = CreateCompatibleDC(hDC_);
	//memHbm_ = CreateCompatibleBitmap(hDC_, WINDOWSIZE.width, WINDOWSIZE.height);
	//oldHbm_ = static_cast<HBITMAP>(SelectObject(memDC_, memHbm_));

	//PatBlt(memDC_, 0, 0, WINDOWSIZE.width, WINDOWSIZE.height, WHITENESS);

	//balls_.move();                               
	//drawTable(); 
	//drawBalls();
		
	//BitBlt(hDC_, 0, 0, WINDOWSIZE.width, WINDOWSIZE.height, memDC_, 0, 0, SRCCOPY);

	//SelectObject(memDC_, oldHbm_);
	//DeleteObject(memHbm_);
	//DeleteDC(memDC_);
	
	//EndPaint(hWnd_, &pc);

	if (balls_.stopped()) 
	{
		graphics_->DrawString(L"EZ WIN", strlen("EZ WIN"), font_, PointF(10, 10), brush_);	
		Sleep(500);

		return FALSE;
	}
	else return TRUE;
}
