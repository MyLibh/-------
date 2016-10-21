#include "Cue.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Cue::Cue() :
	texture_(nullptr),
	angle_(0)
{
	GetCursorPos(&mouseCoords_);

	textureSize_.width  = 1100 / 5; // Загнать в константы
	textureSize_.height = 360  / 5;

	textureSize_ *= SCALE;
}

Cue::~Cue()
{
	//delete(texture_);
}

VOID Cue::draw(Graphics *graphics)
{
	//$r dump(); PAUSE

	//reInitImage();
	graphics->RotateTransform(angle_);

	//graphics->DrawImage(texture_, RectF(mouseCoords_.x - textureSize_.width, mouseCoords_.y - textureSize_.height, mouseCoords_.x, mouseCoords_.y));
	graphics->DrawLine(new Pen(Color::Green, 15), Point(mouseCoords_.x - textureSize_.width, mouseCoords_.y - textureSize_.height), Point(mouseCoords_.x, mouseCoords_.y));

	//graphics->DrawImage(new Image(L"Images/Cue.jpg"), RectF(0, 0, textureSize_.width, textureSize_.height));

	graphics->RotateTransform(-angle_);
	//graphics->ResetTransform(); // Что за функция?
}

VOID Cue::rotate()
{
	//angle_++;
}