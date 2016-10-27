#include "Variables.hpp"

#pragma once

class Mouse
{
private:
    POINT mouse_;
    INT16 button_;

    VOID setMouseCoords(LPARAM lParam) { mouse_.x = LOWORD(lParam); mouse_.y = HIWORD(lParam); }
    VOID setButton(int button) { button_ = button_; }

public:
    Mouse();
    ~Mouse();

    VOID update(LPARAM lParam, int button) { setMouseCoords(lParam); setButton(button); }

    //VOID setMouseCoords() { }
    //VOID setButton() { }

    POINT getMouseCoords() const { return mouse_; }
    INT16 getButton()      const { return button_; }
};