#include "Button.h"

Button::Button(Control* parent, TSTRING text, int width, int height)
	:Button(parent, text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		{ 0, 0, width, height })
{}

Button::Button(Control* parent, TSTRING text, DWORD style, RECT rect)
	: Control(parent, WC_BUTTON, text.c_str(), style, rect)
{}

Button::~Button()
{
	HICON i = icon();
	if (i) DeleteObject(i);
	HBITMAP b = bitmap();
	if (b) DeleteObject(b);
}

Align Button::textHAlign()
{
	DWORD s = style.get();
	if (s & BS_LEFT) return Left;
	if (s & BS_RIGHT) return Right;
	return Center; // Undefined and Center
}

Align Button::textVAlign()
{
	DWORD s = style.get();
	if (s & BS_TOP) return Top;
	if (s & BS_BOTTOM) return Bottom;
	return Center; // Undefined and VCenter
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

void Button::textHAlign(Align type)
{
	style.subs(BS_CENTER);
	switch (type)
	{
	case Left:
		style.add(BS_LEFT);
		break;
	case Right:
		style.add(BS_RIGHT);
		break;
	}
}

void Button::textVAlign(Align type)
{
	style.subs(BS_VCENTER);
	switch (type)
	{
	case Top:
		style.add(BS_TOP);
		break;
	case Bottom:
		style.add(BS_BOTTOM);
		break;
	}
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

HBITMAP Button::bitmap()
{
	return (HBITMAP)SendMessage(mHwnd, BM_GETIMAGE, IMAGE_BITMAP, NULL);
}

HICON Button::icon()
{
	return (HICON)SendMessage(mHwnd, BM_GETIMAGE, IMAGE_ICON, NULL);
}

void Button::bitmap(HBITMAP bitmap)
{
	HBITMAP old = (HBITMAP)SendMessage(mHwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
	if (old != NULL)
		DeleteObject(old);
}

void Button::icon(HICON icon)
{
	HICON old = (HICON)SendMessage(mHwnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
	if (old != NULL)
		DeleteObject(old);
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