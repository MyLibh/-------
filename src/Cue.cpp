#include "Cue.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Cue::Cue() :
	texture_(nullptr),
	textureSize_(),
	mouseCoords_(),
	angle_(0)
{
	textureSize_.width  = 1100 / 5; // Загнать в константы
	textureSize_.height = 360  / 5; //

	textureSize_ *= static_cast<float>(SCALE);
}

Cue::~Cue()
{
	//delete(texture_);
}

VOID Cue::draw(Graphics *graphics)
{
	$r dump(); 

	//reInitImage();
	graphics->RotateTransform(angle_);

	graphics->DrawImage(texture_, RectF(centerOfSymmetry_.x - textureSize_.width, centerOfSymmetry_.y - textureSize_.height, centerOfSymmetry_.x, centerOfSymmetry_.y));
	graphics->DrawLine(new Pen(Color::Green, 15), Point(centerOfSymmetry_.x - textureSize_.width, centerOfSymmetry_.y - textureSize_.height), Point(centerOfSymmetry_.x, centerOfSymmetry_.y));

	graphics->RotateTransform(-angle_);

	graphics->DrawEllipse(new Pen(Color::Green, 15), static_cast<INT>(centerOfSymmetry_.x - 5), static_cast<INT>(centerOfSymmetry_.y - 5), 5, 5);
}

VOID Cue::rotate(POINT point, LPARAM lParam)
{
	setCenter(point);
	setPosition(lParam);

	angle_ = static_cast<REAL>(atan_(centerOfSymmetry_.x - mouseCoords_.x, centerOfSymmetry_.y - mouseCoords_.y));
}