#include "TextView.h"

TextView::TextView(Control* parent, TSTRING text, int width, int height)
	:TextView(parent, text, WS_CHILD | WS_VISIBLE,
		{ 0, 0, width, height })
{}

TextView::TextView(Control* parent, TSTRING text, DWORD style, RECT rect)
	: Control(parent, WC_STATIC, text.c_str(), style, rect)
{
	if (rect.right == CW_USEDEFAULT) {
		autoSize();
	}
}

void TextView::autoSize()
{
	SIZE s;
	TSTRING str = text();
	HFONT font = (HFONT)SendMessage(mHwnd, WM_GETFONT, NULL, NULL);
	HDC dc = GetDC(mHwnd);
	SelectObject(dc, font);
	GetTextExtentPoint(dc, str.c_str(), str.length(), &s);
	ReleaseDC(mHwnd, dc);
	size(s);
}

TextAlign TextView::align()
{
	// Check that either 01b or 11b is set 
	// since styles are 0, 1 and 2.
	return (TextAlign)(style.get() & 3);
}

Ellipsis TextView::textEllipsis()
{
	// Cause ellipsis is either 0x4000, 0x8000 or
	// 0xC000 which is a combination of both.
	switch (style.get() & 0xC000) {
	case Ellipsis::End: return End;
	case Ellipsis::Path: return Path;
	case Ellipsis::Word: return Word;
	}
	return Ellipsis::None;
}

bool TextView::simple()
{
	return style.has(SS_SIMPLE);
}

bool TextView::sunken()
{
	return style.has(SS_SUNKEN);
}

void TextView::align(TextAlign type)
{
	style.subs(TextAlign::Center);
	style.subs(TextAlign::Right);
	style.add(type);
}

void TextView::textEllipsis(Ellipsis type)
{
	style.subs(Ellipsis::End);
	style.subs(Ellipsis::Path);
	style.subs(Ellipsis::Word);
	if (type != Ellipsis::None)
		style.add(type);
}

void TextView::simple(bool state)
{
	if (state)
		style.add(SS_SIMPLE);
	else
		style.subs(SS_SIMPLE);
}

void TextView::sunken(bool state)
{
	if (state)
		style.add(SS_SUNKEN);
	else
		style.subs(SS_SUNKEN);
}
