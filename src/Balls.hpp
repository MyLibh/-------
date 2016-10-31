#pragma once

#include "Variables.hpp"
#include "Vector.hpp"
#include "Textures.hpp"

using namespace Gdiplus;

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
	bool scored_[NUMBER_OF_BALLS];
	WORD numScored_;

	VOID repulsion();
	VOID repulsionFrom();

protected:
	inline VOID setZeroBallCoords(POINT coords) { t[0] = vec(coords.x, coords.y); }
	inline vec impactDirection(POINT mouse) const { return vec(static_cast<double>(static_cast<INT>((mouse.x - v[0].getX()))%20), static_cast<double>(static_cast<INT>((mouse.y - v[0].getY()))%20)); }

public:	
	Balls();
	~Balls();

	BOOL stopped() const;	

	inline POINT getBallCoords(Textures::TEXTURES index) const { POINT point = { static_cast<LONG>(t[index].getX()), static_cast<LONG>(t[index].getY()) }; return point; }
	
	VOID restart();
	VOID move();
	VOID draw(Graphics*, Image*[]) const;

	
	inline VOID nextMove(POINT mouse) { v[0] = impactDirection(mouse); }
};









