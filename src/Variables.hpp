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
#include "UPOINT.hpp"

using std::cout;
using std::endl;
using std::wstring;

//===========================================================================================================

#define MAX_LOADSTRING 100
#define PAUSE system("pause");

//===========================================================================================================

inline BOOL In(RECT, POINT);

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
	GDIPINIT_FAILED      = -15004,

	ESCAPE               = 27,

	BALLS_STOPPED        =  15001
};


//===========================================================================================================

struct DistanceBetweenWallAndTable
{
	SIZE_T left,
		   up,
		   right,
		   bottom;
};

//Êîíñòàíòû

//==========================================

CONST WORD NUMBER_OF_BALLS = 16;

CONST WORD NUMBER_OF_TEXTURES = NUMBER_OF_BALLS + 1 + 1 + 1 + 1; // background, table, cue, menu

CONST wstring  WAYS[NUMBER_OF_TEXTURES] =
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

enum TEXTURES
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

//==========================================

CONST float SCALE = 0.49f;

CONST Gdiplus::Color COLOR_KEY(0, 197, 206, 5);

//Ìèëëèìåòðû

CONST float tagBALL_DIAMETER = 6.825f;    
CONST float BALL_DIAMETER = tagBALL_DIAMETER * SCALE;   

CONST float tagBALL_RADIUS   = tagBALL_DIAMETER / 2.0f;
CONST float BALL_RADIUS = tagBALL_RADIUS * SCALE;

//Ñàíòèìåòðû

CONST UPOINT tagTABLE_SIZE(384, 206);
CONST UPOINT TABLE_SIZE = (tagTABLE_SIZE * SCALE);

CONST UPOINT tagFIELD_SIZE(355, 177);

CONST SIZE_T tagCUE_LENGTH = 1450;
CONST SIZE_T CUE_LENGTH = tagCUE_LENGTH * static_cast<SIZE_T>(SCALE);

CONST SIZE_T EXTRA_CUE_LENGTH = 30;
CONST SIZE_T EXTRA_CUE_LENGTH_2 = static_cast<SIZE_T>(floor(EXTRA_CUE_LENGTH / 2));

CONST DistanceBetweenWallAndTable tagDISTANCE_BETWEEN_WALL_AND_TABLE = { CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2, CUE_LENGTH + EXTRA_CUE_LENGTH_2 };
#define DistanceBWAT tagDISTANCE_BETWEEN_WALL_AND_TABLE 

///Íà âñÿêèé ñëó÷àé: http://www.billiard-klondayk.ru/razmer-bilyardnoy.htm
//Âèêåïåäèÿ: https://ru.wikipedia.org/wiki/Ïóë_(áèëüÿðä)

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=


CONST double sizestenaUP = 100 * SCALE;//64;//сам
CONST double sizestenaDOWN = 100 * SCALE;//40;//
CONST double sizestenaLEFT = 100 * SCALE;//40;//
CONST double sizestenaRIGHT = 100 * SCALE;//32;//
CONST double sizeXpol = 3550 * SCALE; // sizeX - sizestenaLEFT - sizestenaRIGHT
CONST double sizeYpol = 1775 * SCALE; // sizeY - sizestenaUP - sizestenaDOWN

CONST double sizeX = sizeXpol + sizestenaLEFT + sizestenaRIGHT; //1200;//сумма
CONST double sizeY = sizestenaUP + sizestenaDOWN + sizeYpol; //800;

CONST double cor3 = sqrt(static_cast<double>(3));

CONST INT RShari = static_cast<INT>((68 / 2)  * SCALE); // 16

CONST INT RLuz = static_cast<INT>((72.5 / 2) * SCALE); //RUglLuz = 20
//RBokLuz = 82,5/2 и поменять там где боковые лузы с рлуз на рбоклуз
CONST INT RBokLuz = static_cast<INT>(82.5 / 2);
CONST double Ru = RLuz; // M_SQRT2 * RLuz
CONST INT RDugLuz = static_cast<INT>(15 * SCALE); // 10

CONST INT ColvoCenterDugLuz = 12;

//=============================================================================================================

