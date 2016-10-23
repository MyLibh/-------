#pragma once

#include "Variables.hpp"
#include "Vector.hpp"

using namespace Gdiplus;

class Cue
{
private:
	Image  *texture_;
	UPOINT  textureSize_;

	vec mouse_;
	vec ball_;
	vec cue_;
	vec auxiliaryLine_;

public:
	Cue();
	~Cue();

	VOID dump() { cout << "width: " << textureSize_.width << ", height: " << textureSize_.height << endl
	                   << "mouseX: " << mouse_.getX() << ", mouseY: " << mouse_.getY() << ", angle: " << (mouse_ - ball_).getK() << endl << endl; }

	VOID draw(Graphics*, Pen*, Image*);
	VOID rotate(POINT, LPARAM);
};