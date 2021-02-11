#include "Button.h"

Button::Button(Control* parent, const TSTRING& text, int width, int height)
	:Button(parent, text, { 0, 0, width, height })
{}

Button::Button(Control* parent, const TSTRING& text, RECT&& rect)
	: Button(parent, text, rect)
{}

Button::Button(Control* parent, const TSTRING& text, RECT& rect)
	: Button(parent, text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, &rect)
{}

Button::Button(Control* parent, const TSTRING& text, DWORD style, PRECT rect)
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

ImageButton::ImageButton(Control* parent, HBITMAP bmp, int width, int height)
	:ImageButton(parent, bmp, { 0, 0, width, height })
{}

ImageButton::ImageButton(Control* parent, HBITMAP bmp, RECT&& rect)
	: ImageButton(parent, bmp, rect)
{}

ImageButton::ImageButton(Control* parent, HBITMAP bmp, RECT& rect)
	: ImageButton(parent, bmp, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		&rect)
{}

ImageButton::ImageButton(Control* parent, HBITMAP bmp, DWORD style, PRECT rect)
	: Button(parent, TEXT(""), style, rect)
{
	bitmap(bmp);
}

ImageButton::ImageButton(Control* parent, HICON icn, int width, int height)
	: ImageButton(parent, icn, { 0, 0, width, height })
{}

ImageButton::ImageButton(Control* parent, HICON icn, RECT&& rect)
	: ImageButton(parent, icn, rect)
{}

ImageButton::ImageButton(Control* parent, HICON icn, RECT& rect)
	: ImageButton(parent, icn, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		&rect)
{}

ImageButton::ImageButton(Control* parent, HICON icn, DWORD style, PRECT rect)
	: Button(parent, TEXT(""), style, rect)
{
	icon(icn);
}

CommandLink::CommandLink(Control* parent, const TSTRING& text, int width, int height)
	: CommandLink(parent, text, { 0, 0, width, height })
{}

CommandLink::CommandLink(Control* parent, const TSTRING& text, RECT&& rect)
	: CommandLink(parent, text, rect)
{}

CommandLink::CommandLink(Control* parent, const TSTRING& text, RECT& rect)
	: CommandLink(parent, text, WS_CHILD | WS_VISIBLE | BS_COMMANDLINK, &rect)
{}

CommandLink::CommandLink(Control* parent, const TSTRING& text, DWORD style, PRECT rect)
	: Button(parent, text, style, rect)
{}

TSTRING CommandLink::note()
{
	int len = (int)Button_GetNoteLength(mHwnd) + 1;
	TCHAR* buff = new TCHAR[len];
	Button_GetNote(mHwnd, buff, len);
	TSTRING result = buff; delete[] buff;
	return result;
}

void CommandLink::note(TSTRING text)
{
	Button_SetNote(mHwnd, text.c_str());
}