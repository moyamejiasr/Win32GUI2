#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class TextView: public Control
{
public:
	TextView(Control*, TSTRING, int = CW_USEDEFAULT, int = 13);
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

	Align textAlign();
	bool textEllipsis();
	bool simple();

	void textAlign(Align);
	void textEllipsis(bool);
	void simple(bool);

	////////////////////////////////////////////////////////////
	// Behavior: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No behavior properties */
};

