#pragma once

#include "Variables.hpp"

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
	vec(CONST vec&);
    vec(double, double, BOOL = TRUE);

	VOID dump() const { cout << x_ << y_ << k_ << l_ << l_ * cos(k_) << l_ * sin(k_) << endl << endl; }

	vec& operator=(CONST vec&);
    vec operator=(POINT);
    vec operator+(CONST vec&) const;
	vec operator-(CONST vec&) const;
	vec& operator+=(CONST vec&);
	vec& operator-=(CONST vec&);

    vec operator-=(double);
    vec operator+=(double); 
	vec operator*=(double); 
	vec operator/=(double); 
	vec operator^=(double);	

    vec operator*(double) const;
    vec operator/(double) const;
    vec operator^(double) const;

	inline BOOL operator==(CONST vec &rVec) const { if(x_ == rVec.getX() && y_ == rVec.getY() && k_ == rVec.getK() && l_ == rVec.getL()) return TRUE; return FALSE; }
	inline BOOL operator!=(CONST vec &rVec) const { if(x_ == rVec.getX() && y_ == rVec.getY() && k_ == rVec.getK() && l_ == rVec.getL()) return FALSE; return TRUE; }

	inline double getL() const { return l_; }
	inline double getK() const { return k_; }
	inline double getX() const { return x_; }
	inline double getY() const { return y_; }

	inline VOID setL(double l) { l_ = l; }
	inline VOID setK(double k) { k_ = k; }
	inline VOID setX(double x) { x_ = x; }
	inline VOID setY(double y) { y_ = y; }
	VOID setLK();
    VOID setXY();

	inline REAL toDegrees() const { return static_cast<REAL>(k_ * 180 / M_PI); }

    VOID draw(double, double, Graphics*, Pen&, CONST Color& =  static_cast<ARGB>(Color::Yellow)) const;

    
    };

vec xy_vec(double, double);
vec lk_vec(double, double);

