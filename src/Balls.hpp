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
	vec  points_[NUMBER_OF_BALLS];
	vec  speeds_[NUMBER_OF_BALLS];
    BOOL scored_[NUMBER_OF_BALLS];
	WORD numScored_;

	VOID repulsion();
	VOID repulsionFrom();

protected:
	inline VOID setZeroBallCoords(POINT coords) { points_[0] = vec(coords.x, coords.y); }
	inline vec impactDirection(double force, double angle) const { return vec(force, angle, FALSE); }//static_cast<double>((mouse.x - points_[0].getX()) / 40), static_cast<double>((mouse.y - points_[0].getY()) / 40)); }
	inline BOOL ballStopped(Textures::TEXTURES index) const { return !(speeds_[index].getX() && speeds_[index].getY()); }

public:	
	Balls();
	~Balls();

	BOOL stopped() const;	

	inline POINT  getBallCoords(Textures::TEXTURES index) const { POINT point = { static_cast<LONG>(points_[index].getX()), static_cast<LONG>(points_[index].getY()) }; return point; }
	BOOL CONST *getScored() const { return scored_; }

	VOID restart();
	VOID move();
	VOID draw(Graphics*, Image*[]) const;

	inline VOID nextMove(double force, double angle) { speeds_[0] = impactDirection(force, angle); }
};









