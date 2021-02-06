#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class Button: public Control
{
public:
	Button(Control*, TSTRING, int = 75, int = 23);
	Button(Control*, TSTRING, DWORD, RECT);

	DWORD textHAlign();
	DWORD textVAlign();
	bool flat();
	bool multiline();
	bool enhanced();

	void textHAlign(DWORD);
	void textVAlign(DWORD);
	void flat(bool);
	void multiline(bool);
	void enhanced(bool);

protected:
	LRESULT onDraw(HDC hdc);
	LRESULT procedure(UINT, WPARAM, LPARAM);
};

