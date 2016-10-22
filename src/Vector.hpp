#include "Variables.hpp"

#pragma once

using namespace Gdiplus;

double atan_(double, double);

class vec
{
private:
	double x_, y_;
    double k_, l_;

public:
    vec();
    vec(double, double);

	VOID dump() const { cout << x_ << y_ << k_ << l_ << l_ * cos(k_) << l_ * sin(k_) << endl << endl; }

	VOID setL(double l) { l_ = l; }
	VOID setK(double k) { k_ = k; }
	VOID setX(double x) { x_ = x; }
	VOID setY(double y) { y_ = y; }
	VOID setLK();
    VOID setXY();

	double getL() const { return l_; }
	double getK() const { return k_; }
	double getX() const { return x_; }
	double getY() const { return y_; }  

    VOID draw(double, double, Graphics*, Pen*, Color = Color::Yellow);

    vec operator=(vec);
    vec operator=(POINT);
    vec operator+(vec) const;
	vec operator-(vec) const;
	vec operator+=(vec);
	vec operator-=(vec);

    vec operator-=(double);
    vec operator+=(double); 
	vec operator*=(double); 
	vec operator/=(double); 
	vec operator^=(double);	

    vec operator*(double) const;
    vec operator/(double) const;
    vec operator^(double) const;
    };

vec xy_vec(double, double);
vec lk_vec(double, double);

