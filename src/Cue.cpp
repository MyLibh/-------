#include "Cue.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Cue::Cue() :
	texture_(),
	textureSize_(),
	mouse_(),
	ball_(),
	cue_(),
	auxiliaryLine_()
{
	textureSize_.width  = 1100 / 5; // Загнать в константы
	textureSize_.height = 360  / 5; //

	textureSize_ *= static_cast<float>(SCALE);
}

Cue::~Cue()
{
	//delete(texture_);
}

VOID Cue::draw(Graphics *graphics, Pen *pen)
{
	//reInitImage();
	
	cue_.draw((ball_ - cue_).getX(), (ball_ - cue_).getY(), graphics, pen);
	auxiliaryLine_.draw((ball_ - auxiliaryLine_).getX(), (ball_ - auxiliaryLine_).getY(), graphics, pen, Color::Gray);

	pen->SetColor(Color::Gray);
	pen->SetWidth(3);
	graphics->DrawEllipse(pen, static_cast<INT>(mouse_.getX() - RShari / 2), static_cast<INT>(mouse_.getY() - RShari / 2), RShari, RShari);

	//graphics->ResetTransform();
    //graphics->TranslateTransform(ball_.getX(), ball_.getY());
    //graphics->RotateTransform((mouse_ - ball_).getK());

	//graphics->DrawImage(texture_, RectF(cue_.getX(), cue_.getY(), ball_.getX(), ball_.getY()));
}

VOID Cue::rotate(POINT point, LPARAM lParam)
{
	mouse_.setX(LOWORD(lParam));
	mouse_.setY(HIWORD(lParam));

	ball_.setX(point.x);
	ball_.setY(point.y);

	cue_ = mouse_ - ball_;
	auxiliaryLine_ = ball_ - mouse_;

	cue_.setL(CUE_LENGTH);
	cue_.setXY();
	auxiliaryLine_.setXY();
}