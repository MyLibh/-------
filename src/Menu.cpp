#include "Menu.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Menu::Menu() 
{}

Menu::~Menu()
{}

VOID Menu::draw(Graphics *graphics, Image *image, UPOINT windowSize, Pen *pen, Font *font) const
{
    graphics->DrawImage(image, Rect(0, 0, windowSize.width, windowSize.height));

    for(SIZE_T i = 0; i < NUMBER_OF_BUTTONS; i++) buttons_[i].draw(graphics, pen, font);
}

VOID Menu::procedure()
{}
