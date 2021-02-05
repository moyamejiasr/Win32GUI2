#pragma once
#pragma warning (disable : 26495)
#pragma warning (disable : 26812)

#include "EditText.h"

class MultiEditText: public EditText
{
public:
	MultiEditText(Control*, TSTRING, int, int);
	MultiEditText(Control*, TSTRING, DWORD, RECT);
};

