#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class TextView: public Control
{
public:
	TextView(Control*, const TSTRING&, int = CW_USEDEFAULT, int = 13);
	TextView(Control*, const TSTRING&, RECT&&);
	TextView(Control*, const TSTRING&, RECT&);
	TextView(Control*, const TSTRING&, DWORD, PRECT);

	////////////////////////////////////////////////////////////
	// Window: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No common properties */

	////////////////////////////////////////////////////////////
	// Rectangle: Getters & Setters
	////////////////////////////////////////////////////////////

	void autoSize(RECT&);

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

