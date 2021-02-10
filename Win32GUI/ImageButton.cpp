#include "ImageButton.h"

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
