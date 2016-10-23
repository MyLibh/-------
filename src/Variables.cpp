#include "Variables.hpp"

BOOL SetConsoleColor(unsigned color) { return !!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color); }

//====================================================================================================================

UPOINT::UPOINT() :
	width(0),
	height(0)
{}

UPOINT::UPOINT(SIZE_T width, SIZE_T height) :
	width(width),
	height(height)
{}

UPOINT::UPOINT(const UPOINT &upoint)
{
	width  = upoint.width;
	height = upoint.height;
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

/*
template<typename T>
UPOINT & UPOINT::operator*=(T number)
{
	width  *= reinterpret_cast<SIZE_T>(number);
	height *= reinterpret_cast<SIZE_T>(number);

	return *this;
}*/

UPOINT & UPOINT::operator*=(float number)
{
	width  *= static_cast<SIZE_T>(floor(number));
	height *= static_cast<SIZE_T>(floor(number));

	return *this;
}