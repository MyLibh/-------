#include "stdafx.h"
#include "Graphics.hpp"

namespace Billiards
{
	namespace graphics
	{
		Graphics::Graphics(HWND hWnd, CONST UPOINT &rWindowSize) :
			hWnd_(hWnd),
			memDC_(nullptr), 
			memBitmap_(nullptr),
			windowSize_(rWindowSize),
			textures_(),
			pGraphics_(nullptr),
			pPen_(new Pen(static_cast<ARGB>(Color::Yellow, 10))),
			pFont_(new Font(L"Times New Roman", 25, 0, Unit::UnitPoint)),
			pBrush_(new SolidBrush(static_cast<ARGB>(Color::Black)))
		{
			HDC hDC = GetDC(hWnd_);

			memDC_     = CreateCompatibleDC(hDC);
			memBitmap_ = CreateCompatibleBitmap(hDC, windowSize_.width, windowSize_.height);
			SelectObject(memDC_, memBitmap_);

			pGraphics_ = new Gdiplus::Graphics(memDC_);
			
			ReleaseDC(hWnd_, hDC);
		}

		Graphics::~Graphics()
		{
			hWnd_ = nullptr;

			DeleteDC(memDC_);
			DeleteObject(memBitmap_);

			delete(pGraphics_); 
			delete(pPen_);	
			delete(pBrush_);
			delete(pFont_);
		}

		VOID Graphics::drawBalls(CONST vec positions[]) const 
		{
			ImageAttributes imAttr;
			imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);
		
			for(WORD i = 0; i < NUMBER_OF_BALLS; i++)
				pGraphics_->DrawImage(textures_.getBallsTexture()[i], Rect(static_cast<INT>(positions[i].getX()) - RShari, static_cast<INT>(positions[i].getY()) - RShari, 2 * RShari, 2 * RShari), 0, 0, 2 * RShari, 2 * RShari, Unit::UnitPixel, &imAttr, 0);
		}

		VOID Graphics::drawTable() const
		{
			//ImageAttributes imAttr;
			//imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);
			//graphics_->DrawImage(getTableTexture(), RectF(0, 0, static_cast<REAL>(sizeX), static_cast<REAL>(sizeY)), 0, 0, sizeX, sizeY, Unit::UnitPixel, &imAttr, 0); 
			
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

			//for (int i = 0; i < ColvoCenterDugLuz; i++) pGraphics_->DrawEllipse(pPen_, static_cast<INT>(CenterDugLuz[i].getX() - RDugLuz  / 2), static_cast<INT>(CenterDugLuz[i].getY() - RDugLuz / 2), RDugLuz, RDugLuz);
		}

		VOID Graphics::drawCue(CONST vec &rBall, double angle, double force) const
		{
			//auxiliaryLine_.draw((ball_ - auxiliaryLine_).getX(), (ball_ - auxiliaryLine_).getY(), pGraphics, rPen, static_cast<ARGB>(Color::Gray));

			pPen_->SetColor(static_cast<ARGB>(Gdiplus::Color::Gray));
			pPen_->SetWidth(3);
			//pGraphics_->DrawEllipse(pPen_, static_cast<INT>(mouse_.getX() - RShari), static_cast<INT>(mouse_.getY() - RShari), RShari * 2, RShari * 2);

			pGraphics_->TranslateTransform(static_cast<REAL>(rBall.getX()), static_cast<REAL>(rBall.getY()));
			pGraphics_->RotateTransform(static_cast<REAL>(angle)); 
	
			Gdiplus::ImageAttributes imAttr;
			imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);		
			pGraphics_->DrawImage(&textures_.getCueTexture(), Rect(static_cast<INT>(-884 - force * 8), static_cast<INT>(-20 / 2), 884 * 2, 20), 0, 0, 884 * 2, 20, Gdiplus::Unit::UnitPixel, &imAttr, 0);

			pGraphics_->ResetTransform();
		}

		VOID Graphics::drawMenu() const
		{

		}

		VOID Graphics::drawScoreboard() const
		{
		}

		VOID Graphics::setDefaults()
		{
			pPen_->SetColor(Color::Yellow);
			pPen_->SetWidth(10);
		}

		VOID Graphics::drawBufferToCanvas() const 
		{ 
			HDC canvas = GetDC(hWnd_);

			HDC hDC = CreateCompatibleDC(canvas);
			HBITMAP tmp = CreateCompatibleBitmap(canvas, GetDeviceCaps(canvas, HORZRES) / scaleOptions.sx, GetDeviceCaps(canvas, VERTRES) / scaleOptions.sy);
			SelectObject(hDC, tmp);

			StretchBlt(hDC, 0, 0, windowSize_.width / scaleOptions.sx, windowSize_.height / scaleOptions.sy, memDC_, 0, 0, windowSize_.width, windowSize_.height, SRCCOPY); 
			BitBlt(canvas, 0, 0, windowSize_.width, windowSize_.height, hDC, 0, 0, SRCCOPY); 

			DeleteObject(hDC);
			DeleteObject(tmp);

			ReleaseDC(hWnd_, canvas);
			
			std::cout << " " << Billiards::scaleOptions.sx << std::endl;
		}

		VOID Graphics::doGraphics(CONST vec positions[], BOOL drawCue, double angle, double force, BOOL drawMenu) 
		{
			setDefaults();

			if(drawMenu) this->drawMenu();
			else
			{
				//if(drawCue) this->drawCue(vec(100, 100), angle, force);
				drawTable();
				drawBalls(positions);
				//drawScoreboard();		
			}

			drawBufferToCanvas();
			clearBuffer();
		}
	};
};