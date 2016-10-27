#include "Variables.hpp"
#include "Textures.hpp"
#include "Mouse.hpp"

#pragma once

using namespace Gdiplus;

class Menu
{
private:
    static CONST SIZE_T NUMBER_OF_BUTTONS = 4;
    
    CONST WCHAR texts_[NUMBER_OF_BUTTONS];
    CONST RECT buttons_[NUMBER_OF_BUTTONS];

    VOID drawButton(Graphics*, SIZE_T, Pen*, Font*);
    
    Rect RECT2Rect(SIZE_T index) { return Rect(buttons_[index].left, buttons_[index].top, buttons_[index].right - buttons_[index].left, buttons_[index].bottom - buttons_[index].top); }

public:
    Menu();
    ~Menu();

    VOID draw(Graphics*, Image*, UPOINT, Pen*, Font*);
    VOID procedure();
};