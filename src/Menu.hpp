#include "Variables.hpp"
#include "Textures.hpp"
#include "Button.hpp"

#pragma once

using namespace Gdiplus;

class Menu final
{
private:
    static CONST SIZE_T NUMBER_OF_BUTTONS = 4;

    Button buttons_[NUMBER_OF_BUTTONS];
    
	bool inMenu_;

public:
    Menu();
    ~Menu();

	inline BOOL isActive() const { return inMenu_; }

	inline VOID activate()   { inMenu_ =  true; }
	inline VOID deactivate() { inMenu_ = false; }

    VOID draw(Graphics*, Image*, UPOINT, Pen*, Brush*, Font*) const;
    VOID procedure();
};