#include "Menu.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Menu::Menu() 
{}

Menu::~Menu()
{}

VOID Menu::draw(Graphics *graphics, Image *image, UPOINT windowSize, Pen *pen, Brush* brush, Font *font) const
{
    if(inMenu_)
	{
		graphics->DrawImage(image, Rect(0, 0, windowSize.width, windowSize.height));

		for(SIZE_T i = 0; i < NUMBER_OF_BUTTONS; i++) buttons_[i].draw(graphics, pen, brush, font);
	}
}

VOID Menu::procedure()
{
	if(inMenu_)
	{
	}
}
