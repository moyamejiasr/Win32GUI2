#pragma once
#pragma warning (disable : 26495)
#pragma warning (disable : 26812)

#include "EditText.h"

class MultiEditText: public EditText
{
public:
	MultiEditText(Control*, const TSTRING&, int, int = 23);
	MultiEditText(Control*, const TSTRING&, RECT&&);
	MultiEditText(Control*, const TSTRING&, RECT&);
	MultiEditText(Control*, const TSTRING&, DWORD, PRECT);

	void heightInLines(LONG);
};

