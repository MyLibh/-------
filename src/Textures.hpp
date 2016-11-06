#pragma once

#include "Variables.hpp"
#include "Config.hpp"

using namespace Gdiplus;

//=============================================================================================================================

CONST WORD NUMBER_OF_TEXTURES = NUMBER_OF_BALLS + 1 + 1 + 1 + 1; // background, table, cue, menu
CONST wstring WAYS[NUMBER_OF_TEXTURES] =
{ 
	L"../src/Images/0.png",
	L"../src/Images/1.png",
	L"../src/Images/2.png",
	L"../src/Images/3.png",
	L"../src/Images/4.png",
	L"../src/Images/5.png",
	L"../src/Images/6.png",
	L"../src/Images/7.png",
	L"../src/Images/8.png",
	L"../src/Images/9.png",
	L"../src/Images/10.png",
	L"../src/Images/11.png",
	L"../src/Images/12.png",
	L"../src/Images/13.png",
	L"../src/Images/14.png",
	L"../src/Images/15.png",
	L"../src/Images/Background.jpg",
	L"../src/Images/Table.jpg",
	L"../src/Images/Cue.png",
	L"../src/Images/Menu.jpg"
};

class Textures final
{
private:
	Image *pBackground_;
	Image *pTable_;
	Image *pCue_;
	Image *pMenu_;
	mutable Image *pBalls_[NUMBER_OF_BALLS];

	Textures(CONST Textures&) {}
	Textures& operator=(CONST Textures&) {}

public:      
	Textures();
	Textures(CONST Config&);
	~Textures();

	enum Texture
	{
		zero       =  0,
		thirst     =  1,
		second     =  2,
		third      =  3,
		fourth     =  4,
		fifth      =  5,
		sixth      =  6,
		seventh    =  7,
		eighth     =  8,
		nineth     =  9,
		tenth      = 10,
		eleventh   = 11,
		twelfth    = 12,
		thirteenth = 13,
		fourteenth = 14,
		fifteenth  = 15,
		background = 16,
		table      = 17,
		cue        = 18,
		menu       = 19
	};

	inline Image &getBackgroundTexture() const { return *pBackground_; }
	inline Image &getCueTexture()        const { return *pCue_; }
	inline Image &getTableTexture()      const { return *pTable_; }
	inline Image &getMenuTexture()       const { return *pMenu_; }

	inline Image **getBallsTexture()     const { return reinterpret_cast<Image**>(pBalls_); }
};