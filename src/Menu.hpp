#pragma once

#include "Variables.hpp"
#include "Textures.hpp"
#include "Button.hpp"
#include "Balls.hpp"

using namespace Gdiplus;

CONST WORD NUMBER_OF_WTEXTS = 6;
CONST wstring TEXTS[NUMBER_OF_WTEXTS] = 
{
	L"����������",
	L"�����",
	L"���������",
	L"������",
	L"�",
	L"X"

};

class Menu 
{
private:
    static CONST SIZE_T NUMBER_OF_BUTTONS = 4;

    Button buttons_[NUMBER_OF_BUTTONS];
    
	bool inMenu_;

public:
    Menu();
    ~Menu();

	enum ButtonTextsId
	{
		CONTINUE = 0,
		RESTART  = 1, 
		SETTINGS = 2,
		HELP     = 3,
		PROFILE  = 4,
		EXIT     = 5
	};

	enum MenuActions
	{
		Nothing,
		Continue,
		Restart,
		Help,
		Settings,
		Profile
	};

	inline BOOL isActive() const { return inMenu_; }

	inline VOID activate()   { inMenu_ =  true; }
	inline VOID deactivate() { inMenu_ = false; }

    VOID draw(Graphics*, Image&, UPOINT, Pen&, SolidBrush&, Font&) const;
    MenuActions procedure(POINT, INT16);
};