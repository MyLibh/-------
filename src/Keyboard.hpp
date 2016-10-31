#pragma once

#include "Variables.hpp"

#define Key(param) GetAsyncKeyState(param)

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	enum Keys
	{
		ESCAPE = 27,
		SPACE  = 32
	};
};

