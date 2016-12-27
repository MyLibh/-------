#include "stdafx.h"
#include "Vector.hpp"

#pragma comment(lib, "gdiplus.lib")

//using namespace Gdiplus;

double atan(double x, double y)
    {
    if (x == 0) x = 0.00001;

    double returned = atan(y / x);

    if (x < 0) returned += M_PI;

    return returned;
    }

double tan2sin(double tan, BOOL arg /*= true*/)
{
    if (arg)
    {

    }
    else
    {

    }
    return 0;
}

double tan2cos(double tan, BOOL arg /*= true*/)
{
    if (arg)
	{

	}
    else
    {

    }
    return 0;
}

double sin2tan(double sin, BOOL arg /*= true*/)
{
    if (arg)
    {
    }
	else
    {

    }
    return 0;
}

double sin2cos(double sin, BOOL arg /*= true*/)
{
    if (arg)
    {

    }
    else
    {

    }
    return 0;
}

double cos2tan(double cos, BOOL arg /*= true*/)
{
    if (arg)
    {

    }
    else
    {

    }
    return 0;
}

double cos2sin (double cos, BOOL arg /*= true*/)
{
    if (arg) return sqrt (1 - cos * cos);
    else
    {
	}
    return 0;
}

//======================================

vec::vec() :
    x(0),
    y(0),
    l(0)
{}

vec::vec(CONST vec &rVec)
{
	x = rVec.getX();
    y = rVec.getY();
    l = rVec.getL();
}

vec::vec(vec &&rrVec)
{
	x = rrVec.getX();
    y = rrVec.getY();
    l = rrVec.getL();
}

vec::vec(double a, double b, BOOL xy /* = TRUE */)
{
	if(xy)
    {
		x = a;
		y = b;
        l = hypot (a, b);
    }
	else
    {
		x = a * cos(b);
		y = a * sin(b);
		l = a;
    }
}

/*VOID vec::draw(double x0, double y0, Graphics *graphics, Pen &rPen, CONST Color &rColor /* = Color::Yellow *//*) const
    /*{
	rPen.SetColor(rColor);
	rPen.SetWidth(2);

    //graphics->DrawLine(&rPen, Point(static_cast<INT>(x0    ), static_cast<INT>(    y0)), Point(static_cast<INT>(x0 + x), static_cast<INT>(y + y0)));
    //graphics->DrawLine(&rPen, Point(static_cast<INT>(x0 + x), static_cast<INT>(y + y0)), Point(static_cast<INT>(x0 + x - ((l < 0)? -1 : 1) * 5 * cos(k + M_PI_4)), static_cast<INT>(y + y0 - ((l < 0)? -1 : 1) * 5 * sin(k + M_PI_4))));
    //graphics->DrawLine(&rPen, Point(static_cast<INT>(x0 + x), static_cast<INT>(y + y0)), Point(static_cast<INT>(x0 + x - ((l < 0)? -1 : 1) * 5 * cos(k - M_PI_4)), static_cast<INT>(y + y0 - ((l < 0)? -1 : 1) * 5 * sin(k - M_PI_4))));

    l = sqrt(x * x + y * y);
    //k = atan_(x, y);
    }                                                                            */

vec& vec::operator=(CONST vec &rVec)
{
	if (this == &rVec) return *this;

    x = rVec.getX();
    y = rVec.getY();
    l = rVec.getL();

    return *this;
}

vec& vec::operator=(vec &&rrVec)
{
    x = rrVec.getX();
    y = rrVec.getY();
    l = rrVec.getL();
    
    return *this;
}

vec vec::operator=(CONST POINT &rPoint)
{
    x = rPoint.x;
    y = rPoint.y;
    l = hypot(x, y);

    return *this;
}

vec vec::operator+(CONST vec &rVec) const
{
    vec tmp;

    tmp.x = x + rVec.getX();
    tmp.y = y + rVec.getY();
    tmp.l = hypot(tmp.getX(), tmp.getY()); 

    return tmp;
}

vec& vec::operator+=(CONST vec &rVec)
{
    x += rVec.getX();
    y += rVec.getY();
    l = hypot(x, y);

    return *this;
}

vec vec::operator-(CONST vec &rVec) const
{
    vec tmp;

    tmp.x = x - rVec.getX();
    tmp.y = y - rVec.getY();
    tmp.l = hypot(tmp.x, tmp.y);
    
    return tmp;
}

vec& vec::operator-=(CONST vec &rVec)
{
    x -= rVec.getX();
    y -= rVec.getY();
    l = hypot(x, y);
    
    return *this;
}

vec& vec::operator-=(double l1)
{
    if (l >= 0) l -= l1;
    else        l += l1;

    x = l * getCos();
    y = l * getSin();

    return *this;
}

vec& vec::operator+=(double l1)
{
    if (l >= 0) l += l1;
    else        l -= l1;

    x = l * getCos();
    y = l * getSin();

    return *this;
}

vec vec::operator/(double x1) const
{
    vec tmp;

    tmp.l = l / x1;
    tmp.x = x / x1;
    tmp.y = y / x1;

    return tmp;
}

vec& vec::operator/=(double x1)
{
    l /= x1;
    x /= x1;
    y /= x1;

    return *this;
}

vec vec::operator*(double x1) const
{
    vec tmp;

    tmp.l = l * x1;
    tmp.x = x * x1;
    tmp.y = y * x1;

    return tmp;
}

vec& vec::operator*=(double x1)
{
    l *= x1;
    x *= x1;
    y *= x1;

    return *this;
}

vec vec::operator^(double x1) const
{
    double alf = atan(x, y);
    alf += x1;

	vec tmp;
    tmp.l = l;
    tmp.setX(l * cos(alf));
    tmp.setY(l * sin(alf));

    return tmp;
}

vec& vec::operator^=(double x1)
{
    double alf = atan(x, y);
    alf += x1;

    x = l * cos(alf);
    y = l * sin(alf);

    return *this;
}


