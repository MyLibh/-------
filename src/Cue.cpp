#include "Cue.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Cue::Cue() :
	textureSize_(),
	mouse_(),
	ball_(),
	cue_(),
	auxiliaryLine_(),
	draw_(false)
{
	textureSize_.width  = 1100 / 5; // Çàãíàòü â êîíñòàíòû
	textureSize_.height = 360  / 5; //

	textureSize_ *= static_cast<float>(SCALE);
}

Cue::~Cue()
{
	//delete(texture_);
}

VOID Cue::draw(Graphics *graphics, Pen *pen, Image *image)
{	
	if(draw_)
	{
		cue_.draw((ball_ - cue_).getX(), (ball_ - cue_).getY(), graphics, pen);
		auxiliaryLine_.draw((ball_ - auxiliaryLine_).getX(), (ball_ - auxiliaryLine_).getY(), graphics, pen, Color::Gray);

		pen->SetColor(Color::Gray);
		pen->SetWidth(3);
		graphics->DrawEllipse(pen, static_cast<INT>(mouse_.getX() - RShari / 2), static_cast<INT>(mouse_.getY() - RShari / 2), RShari, RShari);

		//graphics->TranslateTransform(static_cast<REAL>(ball_.getX()), static_cast<REAL>(ball_.getY()));
		//graphics->RotateTransform(static_cast<REAL>(atan_(mouse_.getX() - ball_.getX(),  mouse_.getY() - ball_.getY()))); 

		ImageAttributes imAttr;
		imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);		
		graphics->DrawImage(image, Rect(static_cast<INT>(ball_.getX() - 884), static_cast<INT>(ball_.getY() - 20 / 2), 884, 20), 0, 0, 884, 20, Unit::UnitPixel, &imAttr, 0);

		//graphics->ResetTransform();
	}
}

VOID Cue::rotate(POINT point, Mouse mouse)
{
	mouse_.setX(mouse.getMouseCoords().x);
	mouse_.setY(mouse.getMouseCoords().y);

	ball_.setX(point.x);
	ball_.setY(point.y);

	cue_ = mouse_ - ball_;
	auxiliaryLine_ = ball_ - mouse_;

	cue_.setL(CUE_LENGTH);
	cue_.setXY();
	auxiliaryLine_.setXY();
}