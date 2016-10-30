#include "Variables.hpp"
#include "Textures.hpp"
#include "Mouse.hpp"

using namespace Gdiplus;

inline BOOL In(RECT, POINT);

enum MouseButtons
{
	Null  = 0,
	Left  = 1,
	Right = 2
};

//======================================================================================================================

class Button final
{
private:
    static CONST SIZE_T TEXT_SIZE = 16;

    RECT    rect_;
    wstring text_; // Change to image
    bool    active_;

	inline BOOL in(long coord, long less, long more) const { return more >= coord && less <= coord; }
	inline BOOL in(POINT point) const { return in(point.x, rect_.left, rect_.right) && in(point.y, rect_.top, rect_.bottom); }
	inline Rect RECT2Rect() const { return Rect(rect_.left, rect_.top, rect_.right - rect_.left, rect_.bottom - rect_.top); }	

public:
    Button();
    Button(RECT, wstring, bool = FALSE);
	Button(Rect, wstring, bool = FALSE);
    ~Button();   

	inline VOID dump() const { $b cout << __FUNCTION__ << endl; 
								  cout << "rect: { " << rect_.left << ", " << rect_.top << ", " << rect_.right << ", " << rect_.bottom << " }" <<
									      " , text_: " << text_.c_str() << " , active: " << active_ << endl << endl; }

	inline RECT getRECT() const { return rect_; }

    inline VOID deactivate() { active_ =  TRUE; }
    inline VOID activate()   { active_ = FALSE; }

	inline VOID setText(wstring wstr) { text_ = wstr; }
	
	VOID draw(Graphics*, Pen*, Brush*, Font*) const;
	inline BOOL pressed(Mouse mouse) const { return (in(mouse.getCoords()) && mouse.getButton() == MouseButtons::Left)? TRUE : FALSE; }
};