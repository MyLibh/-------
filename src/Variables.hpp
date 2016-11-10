#pragma once

/*
//====================================================================================================================

#pragma warning(push)   
#pragma warning(disable:4514)
#pragma warning(disable:4668)
#pragma warning(disable:4820)

#include <windows.h>

#pragma warning(pop) 

//====================================================================================================================

#pragma warning(push)                 
#pragma warning(disable:4061)
#pragma warning(disable:4263)
#pragma warning(disable:4264)
#pragma warning(disable:4265)
#pragma warning(disable:4365)
#pragma warning(disable:4514)
#pragma warning(disable:4625)
#pragma warning(disable:4626)
#pragma warning(disable:4820)

#include <gdiplus.h>
#include <gdipluspen.h>
#include <gdiplusstringformat.h>
#include <gdipluspath.h>
#include <gdipluslinecaps.h>
#include <gdiplusgraphics.h>
#include <gdiplusheaders.h>


#pragma warning(pop) 

//====================================================================================================================

#pragma warning(push)                 
#pragma warning(disable:4820)

#include <io.h>

#pragma warning(pop) 

//====================================================================================================================

#pragma warning(push)      
#pragma warning(disable:4514)
#pragma warning(disable:4820)

#include <wchar.h>

#pragma warning(pop) 

//====================================================================================================================

#pragma warning(push)      
#pragma warning(disable:4514)

#define _USE_MATH_DEFINES
#include <limits>
#include <cmath>

#pragma warning(pop) 

//====================================================================================================================

#pragma warning(push)  
#pragma warning(disable:4350)
#pragma warning(disable:4710)

#include <xmemory0>

#pragma warning(pop) 

//====================================================================================================================

#pragma warning(push)      
#pragma warning(disable:4350)
#pragma warning(disable:4514)

#include <string>

#pragma warning(pop) 

//====================================================================================================================
*/

#pragma warning(push, 4)
#include <windows.h>

#define _USE_MATH_DEFINES
#include <limits>
#include <cmath>

#include <fstream>
#include <Istream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include <iterator>
#include <locale>
#include <codecvt>
#include <ctime>
#include <io.h>

#include <gdiplus.h>

#include <WinSock.h>
//#include <WS2tcpip.h>

#include "UPOINT.hpp"

#pragma warning(pop)

#include "resource.h"
#include "Uncopyable.hpp"

using namespace std;

//===========================================================================================================

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
	GDIPINIT_FAILED      = -15004,
	NONEBUTTON_PRESSED   = -15005,
	LOGFILECREATE_FAILED = -15006,
	CFGFILECREATE_FAILED = -15007,

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

//==========================================

CONST WORD NUMBER_OF_BALLS = 16;

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


CONST double sizestenaUP = 150 * SCALE;//64;
CONST double sizestenaDOWN = 100 * SCALE;//40;//
CONST double sizestenaLEFT = 100 * SCALE;//40;//
CONST double sizestenaRIGHT = 100 * SCALE;//32;//
CONST double sizeXpol = 3550 * SCALE; // sizeX - sizestenaLEFT - sizestenaRIGHT
CONST double sizeYpol = 1775 * SCALE; // sizeY - sizestenaUP - sizestenaDOWN

CONST double sizeX = sizeXpol + sizestenaLEFT + sizestenaRIGHT; //1200
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

