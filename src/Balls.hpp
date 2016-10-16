#pragma once

#include "Variables.hpp"
#include "vec.hpp"

INT Whatshar(int);

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
	Gdiplus::Image *image_;

	VOID repulsion();
	VOID repulsionFrom();

public:	
	Balls();
	~Balls() { /*for (size_t i = 0; i < NUMBER_OF_BALLS; i++) delete(image_[i]);*/delete image_; }

	BOOL stopped() const;	

	VOID draw(Gdiplus::Graphics*, Gdiplus::Pen*, Gdiplus::Font*, Gdiplus::SolidBrush*) const;
	VOID move();
};









