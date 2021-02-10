#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

// Common callback definitions
typedef std::function<void(Control*, bool)> OnCheckedChange;

class CheckBox : public Control
{
public:
	CheckBox(Control*, TSTRING, int, int = 17);
	CheckBox(Control*, TSTRING, RECT);
	CheckBox(Control*, TSTRING, DWORD, RECT);

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