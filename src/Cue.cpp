#include "Cue.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Cue::Cue() :
	mouse_(),
	ball_(),
	angle_(0),
	auxiliaryLine_()
{
	//textureSize_.width  = 1100 / 5; // Çàãíàòü â êîíñòàíòû
	//textureSize_.height = 360  / 5; //

	//textureSize_ *= SCALE;
}

Cue::~Cue()
{}

VOID Cue::draw(Graphics *graphics, Pen &pen, Image &cue) const
{	
	auxiliaryLine_.draw((ball_ - auxiliaryLine_).getX(), (ball_ - auxiliaryLine_).getY(), graphics, &pen, Color::Gray);

	pen.SetColor(Color::Gray);
	pen.SetWidth(3);
	graphics->DrawEllipse(&pen, static_cast<INT>(mouse_.getX() - RShari), static_cast<INT>(mouse_.getY() - RShari), RShari * 2, RShari * 2);

	graphics->TranslateTransform(static_cast<REAL>(ball_.getX()), static_cast<REAL>(ball_.getY()));
	graphics->RotateTransform(angle_); 
	
	ImageAttributes imAttr;
	imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);		
	graphics->DrawImage(&cue, Rect(-884, static_cast<INT>(-20 / 2), 884 * 2, 20), 0, 0, 884 * 2, 20, Unit::UnitPixel, &imAttr, 0);

	graphics->ResetTransform();
}

VOID Cue::rotate(POINT ball, POINT mouse)
{
	mouse_.setX(mouse.x);
	mouse_.setY(mouse.y);

	ball_.setX(ball.x);
	ball_.setY(ball.y);

	auxiliaryLine_ = ball_ - mouse_;
	auxiliaryLine_.setXY();

	angle_ = (mouse_ - ball_).toDegrees();
}