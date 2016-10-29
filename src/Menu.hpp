#include "Variables.hpp"
#include "Textures.hpp"
#include "Button.hpp"

#pragma once

using namespace Gdiplus;

class Menu
{
private:
    static CONST SIZE_T NUMBER_OF_BUTTONS = 4;

    Button buttons_[NUMBER_OF_BUTTONS];
    
public:
    Menu();
    ~Menu();

    VOID draw(Graphics*, Image*, UPOINT, Pen*, Font*) const;
    VOID procedure();
};