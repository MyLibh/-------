#include "Variables.hpp"

BOOL SetConsoleColor(unsigned color) { return !!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color); }

UPOINT & UPOINT::operator=(RECT rect)
{
	width  = abs(rect.left - rect.right);
	height = abs(rect.right - rect.bottom);

	return *this;
}