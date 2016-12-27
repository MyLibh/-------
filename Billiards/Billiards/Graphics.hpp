#pragma once

#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "stdafx.h"
#include "Vector.hpp"
#include "Textures.hpp"
#include "UPOINT.hpp"

namespace Billiards
{
	struct ScalingOptions 
	{ 
		INT sx, 
		    sy; 

		ScalingOptions(INT x = 1, INT y = 1) : sx(x), sy(y) {}
	};

	static ScalingOptions scaleOptions;

	namespace graphics
	{
		CONST Color COLOR_KEY(0, 197, 206, 5);

		class Graphics final 
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

			VOID drawBalls(CONST vec[]) const;
			VOID drawTable() const;
			VOID drawCue(CONST vec&, double, double) const;
			VOID drawMenu() const;
			VOID drawScoreboard() const;
			inline VOID drawBufferToCanvas() const;
			inline VOID clearBuffer() const { PatBlt(memDC_, 0, 0, windowSize_.width, windowSize_.height, WHITENESS); };

			VOID setDefaults();

		public:
			explicit Graphics(HWND, CONST UPOINT&);
			~Graphics();

			VOID doGraphics(CONST vec[], BOOL, double, double, BOOL);
		};
	};
};

#endif // __GRAPHICS_HPP_INCLUDED__