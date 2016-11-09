#pragma once

#include "Variables.hpp"

class Mouse : private Uncopyable
{
private:
    POINT mouse_;
    INT16 button_;

    inline VOID setMouseCoords(CONST LPARAM &rLParam) { mouse_.x = LOWORD(rLParam); mouse_.y = HIWORD(rLParam); }
    inline VOID setButton(CONST INT16 &rButton) { button_ = rButton; }

public:
    explicit Mouse();
    virtual ~Mouse();

	enum MouseButtons
	{
		Null  = 0,
		Left  = 1,
		Right = 2
	};

	inline VOID dump() const { $y cout << __FUNCTION__ << endl; 
	                              cout << "x: " << mouse_.x << ", y: " << mouse_.y << ", button: " << button_ << endl << endl;}

    inline VOID update(CONST LPARAM &rLParam, CONST INT16 &rButton) { setMouseCoords(rLParam); setButton(rButton); }

    inline VOID setMouseCoords(CONST POINT &rPoint) { SetCursorPos(rPoint.x, rPoint.y); }
    //inline VOID setButton() { }

    inline CONST POINT &getCoords() const { return mouse_; }
	inline CONST LONG  &getX()      const { return mouse_.x; }
	inline CONST LONG  &getY()      const { return mouse_.y; }
    inline CONST INT16 &getButton() const { return button_; }
};