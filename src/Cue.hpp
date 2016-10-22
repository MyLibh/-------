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

	VOID reInitImage() { delete texture_; texture_ = new Image(L"../src/Images/Cue.jpg"); }

public:
	Cue();
	~Cue();

	VOID dump() { cout << "texture: " << texture_ << ", width: " << textureSize_.width << ", height: " << textureSize_.height << endl
	                   << "mouseX: " << mouse_.getX() << ", mouseY: " << mouse_.getY() << ", angle: " << (mouse_ - ball_).getK() << endl << endl; }

	VOID draw(Graphics*, Pen*);
	VOID rotate(POINT, LPARAM);
};