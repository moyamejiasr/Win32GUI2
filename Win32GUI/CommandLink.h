#pragma once
#pragma warning (disable : 26495)

#include "Button.h"

class CommandLink: public Button
{
public:
	CommandLink(Control*, const TSTRING&, int, int = 41); // 58 if two lines
	CommandLink(Control*, const TSTRING&, RECT&&);
	CommandLink(Control*, const TSTRING&, RECT&);
	CommandLink(Control*, const TSTRING&, DWORD, PRECT);

	TSTRING note();

	void note(TSTRING);
};

