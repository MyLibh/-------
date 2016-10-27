#include "Menu.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Menu::Menu() 
{
    
}

Menu::~Menu()
{}

VOID Menu::drawButton(Graphics *graphics, SIZE_T index, Pen *pen, Font *font)
{
    graphics->DrawRectangle(pen, RECT2Rect(index));
    //graphics->DrawString();
}

VOID Menu::draw(Graphics *graphics, Image *image, UPOINT windowSize, Pen *pen, Font *font)
{
    graphics->DrawImage(image, Rect(0, 0, windowSize.width, windowSize.height));

    for(SIZE_T i = 0; i < NUMBER_OF_BUTTONS; i++) drawButton(graphics, i, pen, font);
}

