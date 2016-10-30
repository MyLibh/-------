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

	buttons_[WTEXTS::Continue].setOptions(Rect(X, Y + STEP * 0, WIDTH, HEIGHT), TEXTS[WTEXTS::Continue], FALSE);
	buttons_[WTEXTS::Start].setOptions   (Rect(X, Y + STEP * 0, WIDTH, HEIGHT), TEXTS[WTEXTS::Start]);
	buttons_[WTEXTS::Help].setOptions    (Rect(X, Y + STEP * 1, WIDTH, HEIGHT), TEXTS[WTEXTS::Help]);
	buttons_[WTEXTS::Settings].setOptions(Rect(X, Y + STEP * 2, WIDTH, HEIGHT), TEXTS[WTEXTS::Settings]);

	buttons_[WTEXTS::Profile].setOptions(Rect(0, 0, 100, 100), TEXTS[WTEXTS::Profile]);
}

Menu::~Menu()
{}

VOID Menu::draw(Graphics *graphics, Image *image, UPOINT windowSize, Pen *pen, SolidBrush* brush, Font *font) const
{
	graphics->DrawImage(image, Rect(0, 0, windowSize.width, windowSize.height));

	for(SIZE_T i = 0; i < NUMBER_OF_BUTTONS; i++) buttons_[i].draw(graphics, pen, brush, font);
}

VOID Menu::procedure(Mouse mouse, Balls *balls) 
{
	for(size_t i = 0; i < NUMBER_OF_BUTTONS; i++)
		if(buttons_[i].pressed(mouse))//!!
			switch(i)
			{
			case WTEXTS::Continue:
				deactivate();
				break;
			case WTEXTS::Start:
				deactivate();
				balls->restart();
				break;
			case WTEXTS::Help:
				// Help
				break;
			case WTEXTS::Settings: 
				// Settings
				break;
			case WTEXTS::Profile:
				// Profile
				break;
			default:
				PostQuitMessage(EXITS::NONEBUTTON_PRESSED);
			}
}
