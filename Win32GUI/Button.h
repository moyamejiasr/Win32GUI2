#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class Button: public Control
{
public:
	Button(Control*, const TSTRING&, int = 75, int = 23);
	Button(Control*, const TSTRING&, RECT&&);
	Button(Control*, const TSTRING&, RECT&);
	Button(Control*, const TSTRING&, DWORD, PRECT);
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
	LRESULT procedure(UINT, WPARAM, LPARAM);
};

