#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <Istream>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <io.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "resource.h"

using std::cout;
using std::endl;
//===========================================================================================================

#define MAX_LOADSTRING 100
#define PAUSE system("pause");

//===========================================================================================================

BOOL SetConsoleColor(unsigned); 

#define $r SetConsoleColor(0x0c);
#define $g SetConsoleColor(0x0a);
#define $b SetConsoleColor(0x09);
#define $y SetConsoleColor(0x0e);

enum EXITS
{
	WNDCLASS_FAILED      = -15001,
	WNDCREATE_FAILED     = -15002,
	CONSOLECREATE_FAILED = -15003,

	ESCAPE           = 27,

	BALLS_STOPPED    =  15001
};


//===========================================================================================================

struct DistanceBetweenWallAndTable
{
	SIZE_T left,
		   up,
		   right,
		   bottom;
};

struct UPOINT
{
	size_t width,
		   height;

	UPOINT();
	UPOINT(SIZE_T, SIZE_T);
	UPOINT(const UPOINT&);
	~UPOINT();

	UPOINT &operator=(RECT);
	UPOINT &operator=(UPOINT);
	UPOINT operator*(float) const;
	UPOINT operator*(UPOINT) const;

	//template<typename T>
	//UPOINT& operator*=(T);
	UPOINT &operator*=(float);
};

//Константы

CONST float SCALE = 2.13f;
CONST WORD NUMBER_OF_BALLS = 16;
CONST Gdiplus::Color COLOR_KEY(0, 197, 206, 5);

//Миллиметры

CONST float tagBALL_DIAMETER = 6.825f;    
CONST float BALL_DIAMETER = tagBALL_DIAMETER * SCALE;   

CONST float tagBALL_RADIUS   = tagBALL_DIAMETER / 2.0f;
CONST float BALL_RADIUS = tagBALL_RADIUS * SCALE;

//Сантиметры

CONST UPOINT tagTABLE_SIZE(384, 206);
CONST UPOINT TABLE_SIZE = (tagTABLE_SIZE * SCALE);

CONST UPOINT tagFIELD_SIZE(355, 177);

CONST SIZE_T tagCUE_LENGTH = 145;
CONST SIZE_T CUE_LENGTH = tagCUE_LENGTH * static_cast<SIZE_T>(SCALE);

CONST SIZE_T EXTRA_CUE_LENGTH = 30;
CONST SIZE_T EXTRA_CUE_LENGTH_2 = static_cast<SIZE_T>(floor(EXTRA_CUE_LENGTH / 2));

CONST DistanceBetweenWallAndTable tagDISTANCE_BETWEEN_WALL_AND_TABLE = { CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2 };
#define DistanceBWAT tagDISTANCE_BETWEEN_WALL_AND_TABLE 

///На всякий случай: http://www.billiard-klondayk.ru/razmer-bilyardnoy.htm
//Викепедия: https://ru.wikipedia.org/wiki/Пул_(бильярд)

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

CONST double sizeX = 1200;
CONST double sizeY = 800;
CONST double sizestenaUP = 64;
CONST double sizestenaDOWN = 40;
CONST double sizestenaLEFT = 40;
CONST double sizestenaRIGHT = 32;
CONST double sizeXpol = sizeX - sizestenaLEFT - sizestenaRIGHT;
CONST double sizeYpol = sizeY - sizestenaUP - sizestenaDOWN;

CONST double cor3 = sqrt(static_cast<double>(3));

CONST INT RShari = 16;

CONST INT RLuz = 20;
CONST double Ru = M_SQRT2 * RLuz;
CONST INT RDugLuz = 10;            

CONST INT ColvoCenterDugLuz = 12;

//=============================================================================================================

