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
	~UPOINT();

	UPOINT &operator=(RECT);
	UPOINT &operator=(UPOINT);

	//template<typename T>
	//UPOINT& operator*=(T);
	UPOINT &operator*=(float);
};

//Константы

CONST double SCALE = 2.13;
CONST WORD NUMBER_OF_BALLS = 16;

//Миллиметры

CONST float BALL_DIAMETER = 68.25f;                
CONST float BALL_RADIUS   = BALL_DIAMETER / 2.0f;

//Сантиметры

CONST UPOINT TABLE_SIZE(384, 206);
CONST UPOINT FIELD_SIZE(355, 177);

CONST SIZE_T CUE_LENGTH = 145;
CONST SIZE_T EXTRA_CUE_LENGTH = 30;
CONST SIZE_T EXTRA_CUE_LENGTH_2 = static_cast<SIZE_T>(floor(EXTRA_CUE_LENGTH / 2));

CONST DistanceBetweenWallAndTable DISTANCE_BETWEEN_WALL_AND_TABLE = { CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2 };
#define DistanceBWAT DISTANCE_BETWEEN_WALL_AND_TABLE

///На всякий случай: http://www.billiard-klondayk.ru/razmer-bilyardnoy.htm
//Викепедия: https://ru.wikipedia.org/wiki/Пул_(бильярд)

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=

CONST double sizeX = 1200;
CONST double sizeY = 700;
CONST double sizestenaUP = 64;
CONST double sizestenaDOWN = 40;
CONST double sizestenaLEFT = 40;
CONST double sizestenaRIGHT = 32;
CONST double sizeXpol = sizeX - sizestenaLEFT - sizestenaRIGHT;
CONST double sizeYpol = sizeY - sizestenaUP - sizestenaDOWN;

CONST double cor3 = sqrt(static_cast<double>(3));

CONST INT RShari = 15;

CONST INT RLuz = 20;
CONST double Ru = M_SQRT2 * RLuz;
CONST INT RDugLuz = 10;            

CONST INT ColvoCenterDugLuz = 12;

//=============================================================================================================

