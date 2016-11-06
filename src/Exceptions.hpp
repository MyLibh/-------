#pragma once

#include "Variables.hpp"

//=============================================================================================================================

class WindowException 
{
private:
	HWND hWnd_;

protected:
	inline VOID dump() const { cout << hWnd_; }

public:
	explicit WindowException();
	WindowException(HWND); 
};

class Exceptions final : private WindowException
{
public:

};