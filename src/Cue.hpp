#pragma once

#include "Variables.hpp"
#include "Vector.hpp"
#include "Mouse.hpp"

using namespace Gdiplus;

//=============================================================================================================================

class Cue 
{
private:
	vec mouse_;
	vec ball_;
	vec auxiliaryLine_;

	REAL angle_;

	BOOL draw_;

	Cue(CONST Cue&) {}
	Cue& operator=(CONST Cue&) {}

public:
	explicit Cue();
	~Cue();

	inline VOID dump() const { $g cout << __FUNCTION__ << endl;
								  cout << "mouseX: " << mouse_.getX() << ", mouseY: " << mouse_.getY() << ", angle: " << atan_(mouse_.getX() - ball_.getX(),  mouse_.getY() - ball_.getY()) << endl << endl; }

	inline double getAngleInRadians() const { return static_cast<double>(angle_ * M_PI / 180); }
	inline double getAngleInDegrees() const { return static_cast<double>(angle_); }

	inline VOID activate()   { draw_ =  TRUE; }
	inline VOID deactivate() { draw_ = FALSE; }

	VOID draw(Graphics*, Pen&, Image&) const;
	VOID rotate(CONST POINT&, CONST POINT&);
};