#pragma once
#pragma warning (disable : 26495)
#pragma warning (disable : 26812)

#include "Control.h"

enum Ellipsis {
	None = 0x0,
	End = SS_ENDELLIPSIS,
	Path = SS_PATHELLIPSIS,
	Word = SS_WORDELLIPSIS
};

class TextView: public Control
{
public:
	TextView(Control*, TSTRING, int = CW_USEDEFAULT, int = CW_USEDEFAULT);
	TextView(Control*, TSTRING, DWORD, RECT);

	////////////////////////////////////////////////////////////
	// Window: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No common properties */

	////////////////////////////////////////////////////////////
	// Rectangle: Getters & Setters
	////////////////////////////////////////////////////////////

	void autoSize();

	////////////////////////////////////////////////////////////
	// Appearance: Getters & Setters
	////////////////////////////////////////////////////////////

	TextAlign align();
	Ellipsis textEllipsis();
	bool simple();
	bool sunken();

	void align(TextAlign);
	void textEllipsis(Ellipsis);
	void simple(bool);
	void sunken(bool);

	////////////////////////////////////////////////////////////
	// Behavior: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No behavior properties */

};

