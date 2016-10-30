#include "Variables.hpp"

BOOL SetConsoleColor(unsigned color) { return !!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color)); }

//====================================================================================================================

