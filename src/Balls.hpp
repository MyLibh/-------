#pragma once

#include "Variables.hpp"
#include "Vector.hpp"

CONST vec CenterDugLuz[ColvoCenterDugLuz] =
    { 
    vec(sizeX - sizestenaRIGHT + RDugLuz,            sizestenaUP + Ru + RDugLuz),
    vec(sizeX - sizestenaRIGHT + RDugLuz, sizeYpol + sizestenaUP - Ru - RDugLuz),
    vec(        sizestenaLEFT  - RDugLuz,            sizestenaUP + Ru + RDugLuz),
    vec(        sizestenaLEFT  - RDugLuz, sizeYpol + sizestenaUP - Ru - RDugLuz),
    vec(sizestenaLEFT + Ru + RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
    vec(sizeXpol / 2 + sizestenaLEFT - RLuz - RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
    vec(sizeXpol + sizestenaLEFT - Ru - RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
    vec(sizeXpol / 2 + sizestenaLEFT + RLuz + RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
    vec(sizestenaLEFT + Ru + RDugLuz,                        sizestenaUP - RDugLuz),
    vec(sizeXpol / 2 + sizestenaLEFT - RLuz - RDugLuz,            sizestenaUP - RDugLuz),
    vec(sizeXpol + sizestenaLEFT - Ru - RDugLuz,                  sizestenaUP - RDugLuz),
    vec(sizeXpol / 2 + sizestenaLEFT + RLuz + RDugLuz,            sizestenaUP - RDugLuz),
    };

class Balls
{
private:
	vec t[NUMBER_OF_BALLS];
	vec v[NUMBER_OF_BALLS];
	int golled;

	VOID repulsion();
	VOID repulsionFrom();

public:	
	Balls();
	~Balls();

	BOOL stopped() const;	

	POINT getBitokCoords() const { POINT point = { static_cast<LONG>(t[0].getX()), static_cast<LONG>(t[0].getY()) }; return point; }
	
	VOID move();
	VOID draw(Gdiplus::Graphics*, Gdiplus::Image*, size_t); 
};









