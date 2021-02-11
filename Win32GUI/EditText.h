#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class EditText : public Control
{
public:
	EditText(Control*, const TSTRING& text, int, int = 23);
	EditText(Control*, const TSTRING&, RECT&&);
	EditText(Control*, const TSTRING&, RECT&);
	EditText(Control*, const TSTRING&, DWORD, PRECT);

	////////////////////////////////////////////////////////////
	// Window: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No common properties */

	////////////////////////////////////////////////////////////
	// Rectangle: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No rectangle properties */

	////////////////////////////////////////////////////////////
	// Appearance: Getters & Setters
	////////////////////////////////////////////////////////////

	Align textAlign();
	bool lowercase();
	bool number();
	bool uppercase();

	void textAlign(Align);
	void lowercase(bool);
	void number(bool);
	void uppercase(bool);

	////////////////////////////////////////////////////////////
	// Behavior: Getters & Setters
	////////////////////////////////////////////////////////////

	bool keepSelection();
	bool password();
	bool readonly();

	void keepSelection(bool);
	void password(bool);
	void readonly(bool);

protected:
	virtual LRESULT procedure(UINT, WPARAM, LPARAM);
};

class MultiEditText : public EditText
{
public:
	MultiEditText(Control*, const TSTRING&, int, int = 23);
	MultiEditText(Control*, const TSTRING&, RECT&&);
	MultiEditText(Control*, const TSTRING&, RECT&);
	MultiEditText(Control*, const TSTRING&, DWORD, PRECT);

	void heightInLines(LONG);
};