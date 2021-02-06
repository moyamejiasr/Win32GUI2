#pragma once
#pragma warning (disable : 26495)

#include "Button.h"

class CommandLink: public Button
{
public:
	CommandLink(Control*, TSTRING, int, int = 41); // 58 if two lines
	CommandLink(Control*, TSTRING, DWORD, RECT);

	TSTRING note();

	void note(TSTRING);
};

