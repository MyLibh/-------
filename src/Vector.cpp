#include "Vector.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

double atan_(double x, double y)
{
    if (x == 0) x = 0.00001;

    double returned = atan(y / x);

    if (x < 0) returned += M_PI;

    return returned;
} 

//======================================   

vec::vec() :        
    x(0),
    y(0),
    k(0),
    l(0)
{}

vec::vec(double x1, double y1)
{
    x = x1;
    y = y1;
    l = sqrt(x * x + y * y);
    k = atan_(x, y);
}

void vec::print() const { printf ("{%lf, %lf}:{%lf, %lf}:{%lf, %lf}", x, y, k, l, l * cos(k), l * sin(k)); }

void vec::draw(double x0, double y0, HDC hdc)
{
    Graphics *graphics = new Graphics(hdc);
    Pen      *pen      = new Pen(Gdiplus::Color::Yellow, 2);

    graphics->DrawLine(pen, Point(static_cast<INT>(x0    ), static_cast<INT>(    y0)), Point(static_cast<INT>(x0 + x), static_cast<INT>(y + y0)));
    graphics->DrawLine(pen, Point(static_cast<INT>(x0 + x), static_cast<INT>(y + y0)), Point(static_cast<INT>(x0 + x - ((l < 0)? -1 : 1) * 5 * cos(k + M_PI_4)), static_cast<INT>(y + y0 - ((l < 0)? -1 : 1) * 5 * sin(k + M_PI_4))));
    graphics->DrawLine(pen, Point(static_cast<INT>(x0 + x), static_cast<INT>(y + y0)), Point(static_cast<INT>(x0 + x - ((l < 0)? -1 : 1) * 5 * cos(k - M_PI_4)), static_cast<INT>(y + y0 - ((l < 0)? -1 : 1) * 5 * sin(k - M_PI_4))));

    l = sqrt(x * x + y * y);
    k = atan_(x, y);  

    delete(pen);
    delete(graphics);
}

void vec::setXY()
{
    x = l * cos(k);
    y = l * sin(k);
}

void vec::setLK()
{
    l = sqrt(x * x + y * y);
    k = atan_(x, y);
}

vec vec::operator=(vec vec1)
{
	if (this == &vec1) return *this;

    x = vec1.x;
    y = vec1.y;
    l = vec1.l;
    k = vec1.k;

    return *this;
}

vec vec::operator=(POINT xy)
{
    x = xy.x;
    y = xy.y;
    l = sqrt(x * x + y * y);
    k = atan_(x, y);

    return *this;
}

vec vec::operator+(vec vec1) const
{
    vec returned;
    returned.x = x + vec1.x;
    returned.y = y + vec1.y;
    returned.l = sqrt(returned.x * returned.x + returned.y * returned.y);
    returned.k = atan_(returned.x, returned.y);

    return returned;
}

vec vec::operator+=(vec vec1)
{
    vec returned;
    x+= vec1.x;
    y+= vec1.y;
    l = sqrt(x * x + y * y);
    k = atan_(x, y);

    return *this;
}

vec vec::operator-(vec vec1) const
{
    vec returned;
    returned.x = x - vec1.x;
    returned.y = y - vec1.y;
    returned.l = sqrt(returned.x * returned.x + returned.y * returned.y);
    returned.k = atan_(returned.x, returned.y);

    return returned;
}

vec vec::operator-=(vec vec1)
{
    vec returned;
    x = x - vec1.x;
    y = y - vec1.y;
    l = sqrt(x * x + y * y);
    k = atan_(x, y);

    return *this;
}

vec vec::operator-=(double l1)
{
    /*if (l >= 0)*/ 
    //else l+= l1;
	l -= l1;
    x = l * cos(k);
    y = l * sin(k);

    return *this;
}

vec vec::operator+=(double l1)
{
    if (l >= 0) l += l1;
    else        l -= l1;

    x = l * cos(k);
    y = l * sin(k);

    return *this;
}

vec vec::operator/(double x1) const
{
    vec returned;
    returned.l = l / x1;
    returned.k = k;
    returned.x = returned.l * cos(returned.k);
    returned.y = returned.l * sin(returned.k);

    return returned;
}

vec vec::operator/=(double x1)
{
    l /= x1;
    x = l * cos(k);
    y = l * sin(k);

    return *this;
}

vec vec::operator*(double x1) const
{
    vec returned;
    returned.l = l * x1;
    returned.k = k;
    returned.x = returned.l * cos(returned.k);
    returned.y = returned.l * sin(returned.k);

    return returned;
}

vec vec::operator*=(double x1)
{
    l *= x1;
    x = l * cos(k);
    y = l * sin(k);

    return *this;
}

vec vec::operator^(double x1) const
{
    vec returned;
    returned.l = l;
    returned.k = k + x1;
    returned.x = returned.l * cos(returned.k);
    returned.y = returned.l * sin(returned.k);

    return returned;
}

vec vec::operator^=(double x1)
{
    k += x1;
    x = l * cos(k);
    y = l * sin(k);

    return *this;
}

//==========================

vec xy_vec(double x, double y)
{
    vec returned;

    returned.x = x;
    returned.y = y;
    returned.l = sqrt(returned.x * returned.x + returned.y * returned.y);
    returned.k = atan_(returned.x, returned.y);

    return returned;
}

vec lk_vec(double l, double k)
{
    vec returned;

    returned.l = l;
    returned.k = k;
    returned.x = returned.l * cos(returned.k);
    returned.y = returned.l * sin(returned.k);

    return returned;
}