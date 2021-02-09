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

	template<class... _Types>
	void setOnCheckedChange(_Types&&...);

protected:
	OnCheckedChange mOnCheckedChange = NULL;

	virtual void onCheckedChange(bool);
	LRESULT procedure(UINT, WPARAM, LPARAM);
};

template<class ..._Types>
inline void CheckBox::setOnCheckedChange(_Types&& ... args)
{
	mOnCheckedChange = std::bind(std::forward<_Types>(args)...,
		std::placeholders::_1, std::placeholders::_2);
}
