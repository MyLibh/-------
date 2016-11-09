#pragma once

#pragma warning(push)   
#pragma warning(disable:4514)
#pragma warning(disable:4668)
#pragma warning(disable:4820)

#include <windows.h>
#include <winnt.h>

#pragma warning(pop)

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

