#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

class EditText : public Control
{
public:
	EditText(Control*, TSTRING, int, int = 23);
	EditText(Control*, TSTRING, DWORD, RECT);

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
	virtual LRESULT onDraw(HDC);
	virtual LRESULT procedure(UINT, WPARAM, LPARAM);
};


