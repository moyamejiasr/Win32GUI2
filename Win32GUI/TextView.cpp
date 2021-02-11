#include "TextView.h"

TextView::TextView(Control* parent, const TSTRING& text, int width, int height)
	:TextView(parent, text, { 0, 0, width, height })
{}

TextView::TextView(Control * parent, const TSTRING & text, RECT && rect)
	: TextView(parent, text, rect)
{}

TextView::TextView(Control* parent, const TSTRING& text, RECT& rect)
	: TextView(parent, text, WS_CHILD | WS_VISIBLE, &rect)
{
	autoSize(rect);
}

TextView::TextView(Control* parent, const TSTRING& text, DWORD style, PRECT rect)
	: Control(parent, WC_STATIC, text.c_str(), style, rect)
{}

void TextView::autoSize(RECT& r)
{
	SIZE s; TSTRING str = text(); HDC dc = GetDC(mHwnd); 
	SelectObject(dc, (HFONT)SendMessage(mHwnd, WM_GETFONT, NULL, NULL));
	GetTextExtentPoint(dc, str.c_str(), str.length(), &s); 
	ReleaseDC(mHwnd, dc);

	// Apply calculated cx to right if default
	if (r.right == CW_USEDEFAULT)
		r.right = s.cx;
	// Otherwise test for convert DPU
	else if (r.right < 0) 
		r.right = XPixFromXDU(-r.right, mSzChar.cx);

	// Apply calculated cy to bottom if default
	if (r.bottom == CW_USEDEFAULT)
		r.bottom = s.cy;
	// Otherwise test for convert DPU
	else if (r.bottom < 0) 
		r.bottom = YPixFromYDU(-r.bottom, mSzChar.cy);

	// Convert DPU(-) to pixels for the rest
	if (r.left < 0) r.left = XPixFromXDU(-r.left, mSzChar.cx);
	if (r.top < 0) r.top = YPixFromYDU(-r.top, mSzChar.cy);

	// Set rect
	rect(r);
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