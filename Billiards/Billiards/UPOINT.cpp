#include "stdafx.h"
#include "UPOINT.hpp"

UPOINT::UPOINT() :
	width(0),
	height(0)
{}

UPOINT::UPOINT(SIZE_T width, SIZE_T height) :
	width(width),
	height(height)
{}

UPOINT::UPOINT(CONST UPOINT &rUpoint)
{
	width  = rUpoint.width;
	height = rUpoint.height;
}

UPOINT::~UPOINT()
{}

UPOINT & UPOINT::operator=(RECT rect)
{
	width  = abs(rect.left - rect.right);
	height = abs(rect.right - rect.bottom);

	return *this;
}

UPOINT & UPOINT::operator=(UPOINT upoint)
{
	width  = upoint.width;
	height = upoint.height;

	return *this;
}

UPOINT UPOINT::operator*(float number) const { return UPOINT(width  * static_cast<SIZE_T>(number), height * static_cast<SIZE_T>(number)); }

UPOINT UPOINT::operator*(UPOINT upoint) const { return UPOINT(width * upoint.width, height * upoint.height); }

