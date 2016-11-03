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

public:
	enum Ball
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
	};

protected:
	//friend WORD Player::checkScored(CONST BOOL[]);	
	inline VOID setZeroBallCoords(POINT coords) { points_[0] = vec(coords.x, coords.y); }
	inline vec impactDirection(double force, double angle) const { return vec(force, angle, FALSE); }
	inline BOOL ballStopped(Ball index) const { return !(speeds_[index].getX() && speeds_[index].getY()); }

public:	
	Balls();
	~Balls();

	BOOL stopped() const;	

	inline POINT  getBallCoords(Ball index) const { POINT point = { static_cast<LONG>(points_[index].getX()), static_cast<LONG>(points_[index].getY()) }; return point; }
	BOOL CONST *getScored() const { return scored_; }

	VOID restart();
	VOID move();
	VOID draw(Graphics*, Image*[]) const;

	inline VOID nextMove(double force, double angle) { speeds_[0] = impactDirection(force, angle); }
};









