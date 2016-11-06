#pragma once

#include "Variables.hpp"
#include "Textures.hpp"
#include "Mouse.hpp"

using namespace Gdiplus;

//=============================================================================================================================

inline VOID RectEquateRECT(CONST Rect&, RECT&);

//=============================================================================================================================

class Button final
{
private:
    static CONST SIZE_T TEXT_SIZE = 16;

    RECT    rect_;
    wstring text_; // Change to image
    BOOL    active_;

	Button(CONST Button&) {}
	Button& operator=(CONST Button&) {}

	inline BOOL in(CONST LONG& rCoord, CONST LONG& rLess, CONST LONG& rMore) const { return rMore >= rCoord && rLess <= rCoord; }
	inline BOOL in(CONST POINT& rPoint) const { return in(rPoint.x, rect_.left, rect_.right) && in(rPoint.y, rect_.top, rect_.bottom); }
	inline Rect RECT2Rect() const { return Rect(rect_.left, rect_.top, rect_.right - rect_.left, rect_.bottom - rect_.top); }
	inline RectF RECT2RectF() const { return RectF(static_cast<REAL>(rect_.left), static_cast<REAL>(rect_.top), static_cast<REAL>(rect_.right - rect_.left), static_cast<REAL>(rect_.bottom - rect_.top)); }

public:
    Button();
    Button(CONST RECT&, CONST wstring&, CONST BOOL& = FALSE);
	Button(CONST Rect&, CONST wstring&, CONST BOOL& = FALSE);
    ~Button();   

	inline VOID dump() const { $b cout << __FUNCTION__ << endl; 
								  cout << "rect: { " << rect_.left << ", " << rect_.top << ", " << rect_.right << ", " << rect_.bottom << " }" <<
									      " , text_: " << text_.c_str() << " , active: " << active_ << endl << endl; }

	inline CONST RECT &getRECT() const { return rect_; }

    inline VOID deactivate() { active_ =  TRUE; }
    inline VOID activate()   { active_ = FALSE; }

	inline VOID setText(CONST wstring& rWstr) { text_ = rWstr; }
	VOID setOptions(CONST Rect&, CONST wstring&, CONST BOOL& = TRUE);
	
	VOID draw(Graphics*, Pen&, SolidBrush&, CONST Font&) const;
	inline BOOL pressed(CONST POINT& rMouse, CONST INT16& rButton) const { return (in(rMouse) && rButton == Mouse::MouseButtons::Left && active_)? TRUE : FALSE; }
};
