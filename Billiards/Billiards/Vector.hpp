#pragma once

#include "stdafx.h"

//using namespace Gdiplus;

double atan(double, double);

double tan2sin(double, BOOL = true);
double tan2cos(double, BOOL = true);
double sin2tan(double, BOOL = true);
double cos2tan(double, BOOL = true);
double cos2sin(double, BOOL = true);
double sin2cos(double, BOOL = true);

class vec final
{
private:
    double l;
    double x;
	double y;
                                                     
public:
    vec();
	vec(CONST vec&);
	vec(vec&&);
    vec(double, double, BOOL = TRUE);

    vec operator!() const { return vec(x, y) / getLength(); }

	inline __nothrow double getSin() const { return (!(*this)).y; }
	inline __nothrow double getCos() const { return (!(*this)).x; }
	inline __nothrow double getTan() const { return (!(*this)).y / (!(*this)).x; }
	inline __nothrow double getLength() const { return hypot (x, y); }  

	inline __nothrow double getL() const { return l; }
	inline __nothrow double getK() const { return atan(x, y); }
	inline __nothrow double getX() const { return x; }
	inline __nothrow double getY() const { return y; }

    VOID dump() const { std::cout << "x: " << x << ", y: " << y << ", l:  " << "\n\n"; }

	vec& operator=(CONST vec&);
	vec& operator=(vec&&);
    vec  operator=(CONST POINT&);
    vec  operator+(CONST vec&) const;
	vec  operator-(CONST vec&) const;
	vec  operator*(double) const;
    vec  operator/(double) const;
    vec  operator^(double) const;

	vec& operator+=(CONST vec&);
	vec& operator-=(CONST vec&);
    vec& operator-=(double);
    vec& operator+=(double);
	vec& operator*=(double);
	vec& operator/=(double);
	vec& operator^=(double);

	void operator()() const { dump(); }
    //vec operator!=(double length) const { this = vec(x, y)/getLength(); }

	inline BOOL operator==(CONST vec &rVec) const { return (x == rVec.getX() && y == rVec.getY())? TRUE : FALSE; }
	inline BOOL operator!=(CONST vec &rVec) const { return (x == rVec.getX() && y == rVec.getY())? FALSE : TRUE; }

	inline VOID setL(double l_) { l = l_; }
	inline VOID setX(double x_) { x = x_; }
	inline VOID setY(double y_) { y = y_; }
	
	inline __nothrow double toDegrees() const { return static_cast<double>(getK() * 180 / M_PI); }

    //VOID draw(double, double, Graphics*, Pen&, CONST Color& =  static_cast<ARGB>(Color::Yellow)) const;
};

