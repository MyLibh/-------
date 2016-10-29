#pragma once

#include "Variables.hpp"
#include "Vector.hpp"
#include "Mouse.hpp"

using namespace Gdiplus;

class Cue
{
private:
	//UPOINT  textureSize_;

	vec mouse_;
	vec ball_;
	vec cue_;
	vec auxiliaryLine_;

	bool draw_;

public:
	Cue();
	~Cue();

	VOID dump() { cout << "mouseX: " << mouse_.getX() << ", mouseY: " << mouse_.getY() << ", angle: " << atan_(mouse_.getX() - ball_.getX(),  mouse_.getY() - ball_.getY()) << endl << endl; }

	inline VOID activate()   { draw_ =  true; }
	inline VOID deactivate() { draw_ = false; }

	VOID draw(Graphics*, Pen*, Image*) const;
	VOID rotate(POINT, Mouse);
};