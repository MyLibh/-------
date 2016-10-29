#include "Variables.hpp"
#include "Textures.hpp"
#include "Mouse.hpp"

using namespace Gdiplus;

class Button
{
private:
    static CONST SIZE_T TEXT_SIZE = 16;

    RECT  rect_;
    WCHAR text_[TEXT_SIZE]; // Change to image
    bool  active_;

    inline BOOL in(POINT point) const { return In(rect_, point); }
	inline Rect RECT2Rect() const { return Rect(rect_.left, rect_.top, rect_.right - rect_.left, rect_.bottom - rect_.top); }

public:
    Button();
    Button(RECT, WCHAR[]);
    ~Button();   

	inline RECT getRECT() const { return rect_; }

    inline VOID deactivate() { active_ =  TRUE; }
    inline VOID activate()   { active_ = FALSE; }

	inline VOID setText(WCHAR src[]) { wcsncpy_s(text_, src, TEXT_SIZE * sizeof(WCHAR)); }
	
	VOID draw(Graphics*, Pen*, Font*) const;
    inline BOOL pressed(Mouse mouse) const { return (in(mouse.getMouseCoords()) && mouse.getButton() == 1)? TRUE : FALSE; }
};