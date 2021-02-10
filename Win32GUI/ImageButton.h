#pragma once
#pragma warning (disable : 26495)

#include "Button.h"

class ImageButton: public Button
{
public:
	ImageButton(Control*, HBITMAP, int = 75, int = 23);
	ImageButton(Control*, HBITMAP, RECT&&);
	ImageButton(Control*, HBITMAP, RECT&);
	ImageButton(Control*, HBITMAP, DWORD, PRECT);
	ImageButton(Control*, HICON, int = 75, int = 23);
	ImageButton(Control*, HICON, RECT&&);
	ImageButton(Control*, HICON, RECT&);
	ImageButton(Control*, HICON, DWORD, PRECT);
};

