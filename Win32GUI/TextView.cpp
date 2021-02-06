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
	GetTextExtentPoint(dc, str.c_str(), (int)str.length(), &s);
	ReleaseDC(mHwnd, dc);
	size(s);
}

Align TextView::textAlign()
{
	DWORD s = style.get();
	if (s & SS_CENTER) return Center;
	if (s & SS_RIGHT) return Right;
	return Left;
}

bool TextView::textEllipsis()
{
	// Check for either 0x4000, 0x8000 or
	// 0xC000 which is a combination of both.
	return style.get() & SS_WORDELLIPSIS;
}

bool TextView::simple()
{
	return style.has(SS_SIMPLE);
}

void TextView::textAlign(Align type)
{
	// Remove both, center(1) and right(2)
	style.subs(3);
	switch (type) 
	{
	case Center:
		style.add(SS_CENTER);
		break;
	case Right:
		style.add(SS_RIGHT);
		break;
	}
}

void TextView::textEllipsis(bool state)
{
	if (state)
		style.add(SS_WORDELLIPSIS);
	else
		style.subs(SS_WORDELLIPSIS);
}

void TextView::simple(bool state)
{
	if (state)
		style.add(SS_SIMPLE);
	else
		style.subs(SS_SIMPLE);
}