#pragma once

#include "Variables.hpp"
#include "Vector.hpp"

using namespace Gdiplus;

class Cue
{
private:
	Image  *texture_;
	UPOINT  textureSize_;
	POINT   mouseCoords_;
	POINT   centerOfSymmetry_;
	REAL    angle_;

	VOID reInitImage() { delete texture_; texture_ = new Image(L"../src/Images/Cue.jpg"); }
public:
	Cue();
	~Cue();

	VOID dump() { cout << "texture: " << texture_ << ", width: " << textureSize_.width << ", height: " << textureSize_.height << endl
	                   << "mouseX: " << mouseCoords_.x << ", mouseY: " << mouseCoords_.y << ", angle: " << angle_ << endl << endl; }

	VOID setPosition(LPARAM lParam) { mouseCoords_.x = LOWORD(lParam); mouseCoords_.y = HIWORD(lParam); }
	VOID setCenter(POINT point) { centerOfSymmetry_ = point; }

	VOID draw(Graphics*);
	VOID rotate(POINT, LPARAM);
};