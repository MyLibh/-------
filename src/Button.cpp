#include "Button.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Button::Button()
{}

Button::~Button()
{}

VOID Button::draw(Graphics *graphics, Pen *pen, Font *font) const
{
	graphics->DrawRectangle(pen, RECT2Rect());
	//graphics->DrawString();
}