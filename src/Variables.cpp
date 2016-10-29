#include "Variables.hpp"

BOOL SetConsoleColor(unsigned color) { return !!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color); }

//====================================================================================================================

inline BOOL In(RECT rect, POINT point)
{
	return(rect.left <= point.x && rect.right >= point.x && rect.bottom <= point.y && rect.top >= point.y)? TRUE : FALSE;
}