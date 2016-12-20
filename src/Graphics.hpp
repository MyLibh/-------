#pragma once

#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "Vector.hpp"
#include "Textures.hpp"

namespace Billiards
{
	namespace graphics
	{
		CONST Gdiplus::Color COLOR_KEY(0, 197, 206, 5);

		class Graphics
		{
		private:
			HWND                 hWnd_;
			HDC                  memDC_;
			HBITMAP              memBitmap_;

			UPOINT               windowSize_;
			Textures             textures_;

			Gdiplus::Graphics   *pGraphics_;
			Gdiplus::Pen        *pPen_;
			Gdiplus::SolidBrush *pBrush_;
			Gdiplus::Font       *pFont_;

			VOID drawBall(CONST vec&, WORD) const;
			VOID drawBalls(CONST vec&) const;
			VOID drawTable() const;
			VOID drawCue(CONST vec&, double, double) const;
			VOID drawMenu() const;
			VOID drawScoreboard() const;
			inline VOID drawBufferToCanvas() const;

		protected:
			VOID doGraphics(CONST vec&, BOOL, double, double, BOOL) const;	

		public:
			explicit Graphics(HWND, CONST UPOINT&);
			~Graphics();
		};
	};
};

#endif // __GRAPHICS_HPP_INCLUDED__