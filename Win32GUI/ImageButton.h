#pragma once
#pragma warning (disable : 26495)

#include "Button.h"

class ImageButton: public Button
{
public:
	ImageButton(Control*, TSTRING, int = 75, int = 23);
	ImageButton(Control*, TSTRING, DWORD, RECT);
};

