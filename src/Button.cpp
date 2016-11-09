#include "Button.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

inline BOOL In(RECT rect, POINT point)
{
	return(rect.left <= point.x && rect.right >= point.x && rect.bottom <= point.y && rect.top >= point.y)? TRUE : FALSE;
}

inline VOID RectEquateRECT(CONST Rect &rSource, RECT &rDest)
{
	rDest.left   = rSource.GetLeft();
	rDest.top    = rSource.GetTop();
	rDest.right  = rSource.GetRight();
	rDest.bottom = rSource.GetBottom();
}

//=============================================================================================================================

Button::Button() : 
	rect_(),
	text_(L""),
	active_(FALSE)
{}

Button::Button(CONST RECT &rRect, CONST wstring &rText, CONST BOOL &rActive /* = FALSE */) :
	rect_(rRect),
	text_(rText),
	active_(rActive)
{}

Button::Button(CONST Rect &rRect, CONST wstring &rText, CONST BOOL &rActive /* = FALSE */) :
	text_(rText),
	active_(rActive)
{
	RectEquateRECT(rRect, rect_);
}

Button::~Button()
{}

VOID Button::setOptions(CONST Rect &rRect, CONST wstring &rText, CONST BOOL &rActive /* = FALSE */)
{
	RectEquateRECT(rRect, rect_);

	text_ = rText;

	active_ = rActive;
}

VOID Button::draw(Graphics *pGraphics, Pen &rPen, SolidBrush &rBrush, CONST Font &/*rFont*/) const
{
	rPen.SetColor(Color(5, 159, 225));
	rPen.SetWidth(3);
	rBrush.SetColor(Color(255, 125, 34));
	
	pGraphics->DrawRectangle(&rPen, RECT2Rect());
	//graphics->DrawString(text_.c_str(), text_.length(), &font, PointF(RECT2RectF().GetLeft(), RECT2RectF().GetTop()), &brush);
}
