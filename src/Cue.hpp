#pragma once

#include "Variables.hpp"
#include "Vector.hpp"
#include "Mouse.hpp"

using namespace Gdiplus;

class Cue
{
private:public:
	Image  *texture_;
	UPOINT  textureSize_;

	vec mouse_;
	vec ball_;
	vec cue_;
	vec auxiliaryLine_;

	bool draw_;


	Cue();
	~Cue();

	VOID dump() { cout << "width: " << textureSize_.width << ", height: " << textureSize_.height << endl
	                   << "mouseX: " << mouse_.getX() << ", mouseY: " << mouse_.getY() << ", angle: " << (mouse_ - ball_).getK() << endl << endl; }

	VOID draw(Graphics*, Pen*, Image*);
	VOID rotate(POINT, Mouse);
};