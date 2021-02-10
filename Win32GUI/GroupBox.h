#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class GroupBox: public Control
{
public:
	GroupBox(Control*, const TSTRING&, int, int);
	GroupBox(Control*, const TSTRING&, RECT&&);
	GroupBox(Control*, const TSTRING&, RECT&);
	GroupBox(Control*, const TSTRING&, DWORD, PRECT);

protected:
	static LRESULT CALLBACK GroupSubClass(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
};

