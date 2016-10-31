#include "Menu.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Menu::Menu() 
{
	CONST INT WIDTH  = 493;
	CONST INT HEIGHT = 170;
	CONST INT X      = 1175;
	CONST INT Y      = 224;
	CONST INT STEP   = 200;

	buttons_[ButtonTextsId::CONTINUE].setOptions(Rect(X, Y + STEP * 0, WIDTH, HEIGHT), TEXTS[ButtonTextsId::CONTINUE], FALSE);
	buttons_[ButtonTextsId::RESTART].setOptions (Rect(X, Y + STEP * 0, WIDTH, HEIGHT), TEXTS[ButtonTextsId::RESTART]);
	buttons_[ButtonTextsId::HELP].setOptions    (Rect(X, Y + STEP * 1, WIDTH, HEIGHT), TEXTS[ButtonTextsId::HELP]);
	buttons_[ButtonTextsId::SETTINGS].setOptions(Rect(X, Y + STEP * 2, WIDTH, HEIGHT), TEXTS[ButtonTextsId::SETTINGS]);

	buttons_[ButtonTextsId::PROFILE].setOptions(Rect(0, 0, 100, 100), TEXTS[ButtonTextsId::PROFILE]);
}

Menu::~Menu()
{}

VOID Menu::draw(Graphics *graphics, Image &image, UPOINT windowSize, Pen &pen, SolidBrush &brush, Font &font) const
{
	graphics->DrawImage(&image, Rect(0, 0, windowSize.width, windowSize.height));

	for(SIZE_T i = 0; i < NUMBER_OF_BUTTONS; i++) buttons_[i].draw(graphics, pen, brush, font);
}

Menu::MenuActions Menu::procedure(POINT mouse, INT16 button) 
{
	for(size_t i = 0; i < NUMBER_OF_BUTTONS; i++)
		if(buttons_[i].pressed(mouse, button))//!!
			switch(i)
			{
			case ButtonTextsId::CONTINUE: return MenuActions::Continue;
			case ButtonTextsId::RESTART:  return MenuActions::Restart;
			case ButtonTextsId::HELP:     return MenuActions::Help;
			case ButtonTextsId::SETTINGS: return MenuActions::Settings;
			case ButtonTextsId::PROFILE:  return MenuActions::Profile;
			
			default: PostQuitMessage(EXITS::NONEBUTTON_PRESSED);
			}

	return MenuActions::Nothing;
}
