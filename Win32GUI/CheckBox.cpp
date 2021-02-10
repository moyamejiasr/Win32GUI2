#include "CheckBox.h"

CheckBox::CheckBox(Control* parent, const TSTRING& text, int width, int height)
    :CheckBox(parent, text, { 0, 0, width, height })
{}

CheckBox::CheckBox(Control* parent, const TSTRING& text, RECT&& rect)
    : CheckBox(parent, text, rect)
{}

CheckBox::CheckBox(Control* parent, const TSTRING& text, RECT& rect)
    : CheckBox(parent, text, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, &rect)
{}

CheckBox::CheckBox(Control* parent, const TSTRING& text, DWORD style, PRECT rect)
    : Control(parent, WC_BUTTON, text.c_str(), style, rect)
{}

bool CheckBox::rightCheck()
{
    return style.has(BS_RIGHTBUTTON);
}

bool CheckBox::checked()
{
    return Button_GetCheck(mHwnd) == BST_CHECKED;
}

void CheckBox::rightCheck(bool state)
{
    if (state) style.add(BS_RIGHTBUTTON);
    else style.subs(BS_RIGHTBUTTON);
}

void CheckBox::checked(bool state)
{
    Button_SetCheck(mHwnd, state ? BST_CHECKED : BST_UNCHECKED);
}

void CheckBox::check()
{
    checked(true);
}

void CheckBox::uncheck()
{
    checked(false);
}

void CheckBox::setOnCheckedChange(OnCheckedChange func)
{
    mOnCheckedChange = func;
}

void CheckBox::onCheckedChange(bool state)
{
    if (mOnCheckedChange)
        mOnCheckedChange(this, state);
}

LRESULT CheckBox::procedure(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (HIWORD(wParam))
	{
	case BN_CLICKED:
	{
        onCheckedChange(checked());
	}
	}
	return DefWindowProc(mHwnd, uMsg, wParam, lParam);
}
