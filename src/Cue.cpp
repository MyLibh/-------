#include "Cue.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

Cue::Cue() :
	mouse_(),
	ball_(),
	auxiliaryLine_(),
	angle_(0),
	force_(15),
	draw_(TRUE)
{}

Cue::~Cue()
{}

VOID Cue::draw(Graphics *pGraphics, Pen &rPen, Image &rCue) const
{	
	auxiliaryLine_.draw((ball_ - auxiliaryLine_).getX(), (ball_ - auxiliaryLine_).getY(), pGraphics, rPen, static_cast<ARGB>(Color::Gray));

	rPen.SetColor(static_cast<ARGB>(Color::Gray));
	rPen.SetWidth(3);
	pGraphics->DrawEllipse(&rPen, static_cast<INT>(mouse_.getX() - RShari), static_cast<INT>(mouse_.getY() - RShari), RShari * 2, RShari * 2);

	pGraphics->TranslateTransform(static_cast<REAL>(ball_.getX()), static_cast<REAL>(ball_.getY()));
	pGraphics->RotateTransform(angle_); 
	
	ImageAttributes imAttr;
	imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);		
	pGraphics->DrawImage(&rCue, Rect(static_cast<INT>(-884 - force_ * 8), static_cast<INT>(-20 / 2), 884 * 2, 20), 0, 0, 884 * 2, 20, Unit::UnitPixel, &imAttr, 0);

	pGraphics->ResetTransform();
}

VOID Cue::rotate(CONST POINT &rBall, CONST POINT &rMouse)
{
	mouse_.setX(rMouse.x);
	mouse_.setY(rMouse.y);

	ball_.setX(rBall.x);
	ball_.setY(rBall.y);

	auxiliaryLine_ = ball_ - mouse_;
	auxiliaryLine_.setXY();

	angle_ = (mouse_ - ball_).toDegrees();

	if(Key(VK_UP) && force_ <= 14) force_++;
	else if(Key(VK_DOWN) && force_ >= 2) force_--;
}