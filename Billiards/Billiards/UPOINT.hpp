#pragma once

#include "stdafx.h"

struct UPOINT final
{
	size_t width,
		   height;

	UPOINT();
	UPOINT(SIZE_T, SIZE_T);
	UPOINT(const UPOINT&);
	~UPOINT();

	UPOINT &operator=(RECT);
	UPOINT &operator=(UPOINT);

	UPOINT operator*(float) const;
	UPOINT operator*(UPOINT) const;
};

