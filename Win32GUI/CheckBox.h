#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

// Common callback definitions
typedef std::function<void(Control*, bool)> OnCheckedChange;

class CheckBox : public Control
{
public:
	CheckBox(Control*, const TSTRING&, int, int = 17);
	CheckBox(Control*, const TSTRING&, RECT&&);
	CheckBox(Control*, const TSTRING&, RECT&);
	CheckBox(Control*, const TSTRING&, DWORD, PRECT);

	bool rightCheck();
	bool checked();

	void rightCheck(bool);
	void checked(bool);

	void check();
	void uncheck();

	void setOnCheckedChange(OnCheckedChange);

protected:
	OnCheckedChange mOnCheckedChange = NULL;

	virtual void onCheckedChange(bool);
	LRESULT procedure(UINT, WPARAM, LPARAM);
};