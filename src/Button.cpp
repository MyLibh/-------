#include "Button.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

inline BOOL In(RECT rect, POINT point)
{
	return(rect.left <= point.x && rect.right >= point.x && rect.bottom <= point.y && rect.top >= point.y)? TRUE : FALSE;
}

//=============================================================================================================================

Button::Button() : 
	rect_(),
	text_(L""),
	active_(FALSE)
{}

Button::Button(RECT rect, wstring text, bool active /* = FALSE */) :
	rect_(rect),
	text_(text.begin(), text.end()),
	active_(active)
{}

Button::Button(Rect rect, wstring text, bool active /* = FALSE */) :
	text_(text.begin(), text.end()),
	active_(active)
{
	rect_.left   = rect.GetLeft();
	rect_.top    = rect.GetTop();
	rect_.right  = rect.GetRight();
	rect_.bottom = rect.GetBottom();
}

Button::~Button()
{}

VOID Button::setOptions(Rect rect, wstring text, bool active /* = TRUE */)
{
	rect_.left   = rect.GetLeft();
	rect_.top    = rect.GetTop();
	rect_.right  = rect.GetRight();
	rect_.bottom = rect.GetBottom();

	//std::copy(text.begin(), text.end(), std::back_inserter(text_));

	//text_ = text.substr();

	active_ = active;
}

VOID Button::draw(Graphics *graphics, Pen &pen, SolidBrush &brush, Font &font) const
{
	pen.SetColor(Color(5, 159, 225));
	pen.SetWidth(3);
	brush.SetColor(Color(255, 125, 34));
	

	graphics->DrawRectangle(&pen, RECT2Rect());
	//graphics->DrawString(text_.c_str(), text_.length(), &font, PointF(RECT2RectF().GetLeft(), RECT2RectF().GetTop()), &brush);
}
