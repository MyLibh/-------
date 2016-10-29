#include "Variables.hpp"

#pragma once

class Mouse
{
private:
    POINT mouse_;
    INT16 button_;

    inline VOID setMouseCoords(LPARAM lParam) { mouse_.x = LOWORD(lParam); mouse_.y = HIWORD(lParam); }
    inline VOID setButton(INT16 button) { button_ = button; }

public:
    Mouse();
    ~Mouse();

    inline VOID update(LPARAM lParam, INT16 button) { setMouseCoords(lParam); setButton(button); }

    inline VOID setMouseCoords(POINT point) { SetCursorPos(point.x, point.y); }
    //inline VOID setButton() { }

    inline POINT getMouseCoords() const { return mouse_; }
    inline INT16 getButton()      const { return button_; }
};