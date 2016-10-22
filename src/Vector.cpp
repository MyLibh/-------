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
    x_(0),
    y_(0),
    k_(0),
    l_(0)
{}

vec::vec(double x, double y) :
	x_(x),
    y_(y),
    k_(sqrt(x_ * x_ + y_ * y_)),
    l_(atan_(x_, y_))
{}

VOID vec::draw(double x0, double y0, Graphics *graphics, Pen *pen, Color color /* = Color::Yellow */) 
{
	pen->SetColor(color);
	pen->SetWidth(2);

    graphics->DrawLine(pen, Point(static_cast<INT>(x0     ), static_cast<INT>(     y0)), Point(static_cast<INT>(x0 + x_), static_cast<INT>(y_ + y0)));
    graphics->DrawLine(pen, Point(static_cast<INT>(x0 + x_), static_cast<INT>(y_ + y0)), Point(static_cast<INT>(x0 + x_ - ((l_ < 0)? -1 : 1) * 5 * cos(k_ + M_PI_4)), static_cast<INT>(y_ + y0 - ((l_ < 0)? -1 : 1) * 5 * sin(k_ + M_PI_4))));
    graphics->DrawLine(pen, Point(static_cast<INT>(x0 + x_), static_cast<INT>(y_ + y0)), Point(static_cast<INT>(x0 + x_ - ((l_ < 0)? -1 : 1) * 5 * cos(k_ - M_PI_4)), static_cast<INT>(y_ + y0 - ((l_ < 0)? -1 : 1) * 5 * sin(k_ - M_PI_4))));

    l_ = sqrt(x_ * x_ + y_ * y_);
    k_ = atan_(x_, y_);  
}

VOID vec::setXY()
{
    x_ = l_ * cos(k_);
    y_ = l_ * sin(k_);
}

VOID vec::setLK()
{
    l_ = sqrt(x_ * x_ + y_ * y_);
    k_ = atan_(x_, y_);
}

vec vec::operator=(vec vec1)
{
	if (this == &vec1) return *this;

    x_ = vec1.getX();
    y_ = vec1.getY();
    l_ = vec1.getL();
    k_ = vec1.getK();

    return *this;
}

vec vec::operator=(POINT xy)
{
    x_ = xy.x;
    y_ = xy.y;
    l_ = sqrt(x_ * x_ + y_ * y_);
    k_ = atan_(x_, y_);

    return *this;
}

vec vec::operator+(vec vec1) const
{
    vec returned;

    returned.setX(x_ + vec1.getX());
    returned.setY(y_ + vec1.getY());
    returned.setL(sqrt(returned.getX() * returned.getX() + returned.getY() * returned.getY()));
    returned.setK(atan_(returned.getX(), returned.getY()));

    return returned;
}

vec vec::operator+=(vec vec1)
{
    vec returned;

    x_ += vec1.getX();
    y_ += vec1.getY();
    l_ = sqrt(x_ * x_ + y_ * y_);
    k_ = atan_(x_, y_);

    return *this;
}

vec vec::operator-(vec vec1) const
{
    vec returned;

    returned.setX(x_ - vec1.getX());
    returned.setY(y_ - vec1.getY());
    returned.setL(sqrt(returned.getX() * returned.getX() + returned.getY() * returned.getY()));
    returned.setK(atan_(returned.getX(), returned.getY()));

    return returned;
}

vec vec::operator-=(vec vec1)
{
    vec returned;

    x_ = x_ - vec1.getX();
    y_ = y_ - vec1.getY();
    l_ = sqrt(x_ * x_ + y_ * y_);
    k_ = atan_(x_, y_);

    return *this;
}

vec vec::operator-=(double l1)
{
    /*if (l_ >= 0)*/ 
    //else l_ += l1;
	l_ -= l1;
    x_ = l_ * cos(k_);
    y_ = l_ * sin(k_);

    return *this;
}

vec vec::operator+=(double l1)
{
    if (l_ >= 0) l_ += l1;
    else         l_ -= l1;

    x_ = l_ * cos(k_);
    y_ = l_ * sin(k_);

    return *this;
}

vec vec::operator/(double x1) const
{
    vec returned;

    returned.setL(l_ / x1);
    returned.setK(k_);
    returned.setX(returned.getL() * cos(returned.getK()));
    returned.setY(returned.getL() * sin(returned.getK()));

    return returned;
}

vec vec::operator/=(double x1)
{
    l_ /= x1;
    x_ = l_ * cos(k_);
    y_ = l_ * sin(k_);

    return *this;
}

vec vec::operator*(double x1) const
{
    vec returned;

    returned.setL(l_ * x1);
    returned.setK(k_);
    returned.setX(returned.getL() * cos(returned.getK()));
    returned.setY(returned.getL() * sin(returned.getK()));

    return returned;
}

vec vec::operator*=(double x1)
{
    l_ *= x1;
    x_ = l_ * cos(k_);
    y_ = l_ * sin(k_);

    return *this;
}

vec vec::operator^(double x1) const
{
    vec returned;

    returned.setL(l_);
    returned.setL(k_ + x1);
    returned.setX(returned.getL() * cos(returned.getK()));
    returned.setY(returned.getL() * sin(returned.getK()));

    return returned;
}

vec vec::operator^=(double x1)
{
    k_ += x1;
    x_ = l_ * cos(k_);
    y_ = l_ * sin(k_);

    return *this;
}

//==========================

vec xy_vec(double x, double y)
{
    vec returned;

    returned.setX(x);
    returned.setY(y);
    returned.setL(sqrt(returned.getX() * returned.getX() + returned.getY() * returned.getY()));
    returned.setK(atan_(returned.getX(), returned.getY()));

    return returned;
}

vec lk_vec(double l, double k)
{
    vec returned;

    returned.setL(l);
    returned.setK(k);
    returned.setX(returned.getL() * cos(returned.getK()));
    returned.setY(returned.getL() * sin(returned.getK()));

    return returned;
}