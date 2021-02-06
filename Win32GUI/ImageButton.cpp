#include "ImageButton.h"

ImageButton::ImageButton(Control* parent, TSTRING text, int width, int height)
	:ImageButton(parent, text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP | BS_ICON,
		{ 0, 0, width, height })
{}

ImageButton::ImageButton(Control* parent, TSTRING text, DWORD style, RECT rect)
	: Button(parent, text, style, rect)
{}
