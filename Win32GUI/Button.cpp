#include "Button.h"

Button::Button(Control* parent, TSTRING text, int width, int height)
	:Button(parent, text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		{ 0, 0, width, height })
{}

Button::Button(Control* parent, TSTRING text, DWORD style, RECT rect)
	: Control(parent, WC_BUTTON, text.c_str(), style, rect)
{}

DWORD Button::textHAlign()
{
	// Returns all possibilities for align
	// BS_LEFT | BS_CENTER | BS_RIGHT
	return style.get() & BS_CENTER;
}

DWORD Button::textVAlign()
{
	// Returns all possibilities for align
	// BS_YOP | BS_VCENTER | BS_BOTTOM
	return style.get() & BS_VCENTER;
}

bool Button::flat()
{
	return style.has(BS_FLAT);
}

bool Button::multiline()
{
	return style.has(BS_MULTILINE);
}

bool Button::enhanced()
{
	return style.has(1);
}

void Button::textHAlign(DWORD type)
{
	style.subs(BS_CENTER);
	style.add(type);
}

void Button::textVAlign(DWORD type)
{
	style.subs(BS_VCENTER);
	style.add(type);
}

void Button::flat(bool state)
{
	if (state)
		style.add(BS_FLAT);
	else
		style.subs(BS_FLAT);
}

void Button::multiline(bool state)
{
	if (state)
		style.add(BS_MULTILINE);
	else
		style.subs(BS_MULTILINE);
}

void Button::enhanced(bool state)
{
	// Every style with DEF has 1 as flag
	if (state)
		style.add(1);
	else
		style.subs(1);
}

LRESULT Button::onDraw(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, mFColor);
	SetDCBrushColor(hdc, mBColor);
	return (LRESULT)GetStockObject(DC_BRUSH);
}

LRESULT Button::procedure(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (HIWORD(wParam))
	{
	case BN_CLICKED:
	{
		// Get coordinates related to the main window
		POINT point; GetCursorPos(&point);
		ScreenToClient(GetAncestor(mHwnd, GA_ROOT), &point);
		onClick(WM_LBUTTONDOWN, point);
		break;
	}
	case BN_DBLCLK:
	{
		// Get coordinates related to the main window
		POINT point; GetCursorPos(&point);
		ScreenToClient(GetAncestor(mHwnd, GA_ROOT), &point);
		onDoubleClick(WM_LBUTTONDOWN, point);
		break;
	}
	}
	return DefWindowProc(mHwnd, uMsg, wParam, lParam);
}