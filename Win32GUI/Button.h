#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class Button: public Control
{
public:
	Button(Control*, TSTRING, int = 75, int = 23);
	Button(Control*, TSTRING, DWORD, RECT);
	~Button();

	Align textHAlign();
	Align textVAlign();
	bool flat();
	bool multiline();
	bool enhanced();

	void textHAlign(Align);
	void textVAlign(Align);
	void flat(bool);
	void multiline(bool);
	void enhanced(bool);

	HBITMAP bitmap();
	HICON icon();

	void bitmap(HBITMAP);
	void icon(HICON);

protected:
	LRESULT onDraw(HDC hdc);
	LRESULT procedure(UINT, WPARAM, LPARAM);
};

