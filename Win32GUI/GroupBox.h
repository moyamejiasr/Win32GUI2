#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class GroupBox: public Control
{
public:
	GroupBox(Control*, TSTRING, int, int);
	GroupBox(Control*, TSTRING, RECT);
	GroupBox(Control*, TSTRING, DWORD, RECT);

protected:
	static LRESULT CALLBACK GroupSubClass(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
};

