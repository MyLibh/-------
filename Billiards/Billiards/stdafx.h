#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN

#pragma warning(push, 4)

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>

#include <gdiplus.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <string>

#pragma warning(pop)

#include "Uncopyable.hpp"

//===================================================================================

CONST float SCALE = 0.49f;

CONST WORD NUMBER_OF_BALLS = 16;

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
