#pragma once

#include "Variables.hpp"

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

	inline VOID dump() const { $y cout << __FUNCTION__ << endl; 
	                              cout << "x: " << mouse_.x << ", y: " << mouse_.y << ", button: " << button_ << endl << endl;}

    inline VOID update(LPARAM lParam, INT16 button) { setMouseCoords(lParam); setButton(button); }

    inline VOID setMouseCoords(POINT point) { SetCursorPos(point.x, point.y); }
    //inline VOID setButton() { }

    inline POINT getCoords() const { return mouse_; }
	inline LONG  getX()      const { return mouse_.x; }
	inline LONG  getY()      const { return mouse_.y; }
    inline INT16 getButton() const { return button_; }
};