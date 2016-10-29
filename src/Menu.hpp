#include "Variables.hpp"
#include "Textures.hpp"
#include "Mouse.hpp"

#pragma once

using namespace Gdiplus;

template<typename text_t>
class Button
{
private:
    static CONST SIZE_T TEXT_SIZE = 16;

    RECT   rect_;
    text_t text_[TEXT_SIZE];// Change to image
    bool   active_;

    BOOL in(POINT point) const { return In(rect_, point); }

public:
    Button() : rect_(), text(), active(false) {}
    Button(RECT, text_t[]);
    ~Button();

    Rect RECT2Rect(SIZE_T index) { return Rect(rect_[index].left, rect_[index].top, rect_[index].right - rect_[index].left, rect_[index].bottom - rect_[index].top); }

    VOID draw(Graphics*, Pen*, Font*) const;
    BOOL pressed(Mouse mouse) const { return (in(mouse) && mouse.getButton() == 1)? TRUE : FALSE; }

    VOID deactivate() { active_ =  TRUE; }
    VOID activate()   { active_ = FALSE; }
    
};

class Menu
{
private:
    static CONST SIZE_T NUMBER_OF_BUTTONS = 4;

    //Button buttons_[NUMBER_OF_BUTTONS];
    
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