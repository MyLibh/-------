#include "Variables.hpp"

#pragma once

using namespace Gdiplus;

double atan_(double, double);

class vec final
{
private:
	double x_;
	double y_;
    mutable double l_;
	mutable double k_;

public:
    vec();
    vec(double, double);

	VOID dump() const { cout << x_ << y_ << k_ << l_ << l_ * cos(k_) << l_ * sin(k_) << endl << endl; }

	inline VOID setL(double l) { l_ = l; }
	inline VOID setK(double k) { k_ = k; }
	inline VOID setX(double x) { x_ = x; }
	inline VOID setY(double y) { y_ = y; }
	VOID setLK();
    VOID setXY();

	inline double getL() const { return l_; }
	inline double getK() const { return k_; }
	inline double getX() const { return x_; }
	inline double getY() const { return y_; }  

    VOID draw(double, double, Graphics*, Pen*, Color = Color::Yellow) const;

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

