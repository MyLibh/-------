#include "Variables.hpp"

#pragma once

double atan_(double, double);

class vec
{
public:
    double x, y;
    double k, l;

    vec();
    vec(double, double);

    void setLK();
    void setXY();

    void draw(double, double, HDC);
    void print() const;

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

