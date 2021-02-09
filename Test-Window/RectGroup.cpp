#include "RectGroup.h"

RectGroup::RectGroup(Window* wnd, TSTRING title, TSTRING names[4])
	: GroupBox(wnd, title, { RECT_X, RECT_Y, RECT_W, RECT_H }),
	xlbl(this, names[0], { XLBL_X, XLBL_Y, XLBL_W, XLBL_H }),
	xedt(this, TEXT("0000"), { XEDT_X, XEDT_Y, XEDT_W, XEDT_H }),
	ylbl(this, names[1], { YLBL_X, YLBL_Y, YLBL_W, YLBL_H }),
	yedt(this, TEXT("0000"), { YEDT_X, YEDT_Y, YEDT_W, YEDT_H }),
	wlbl(this, names[2], { WLBL_X, WLBL_Y, WLBL_W, WLBL_H }),
	wedt(this, TEXT("0000"), { WEDT_X, WEDT_Y, WEDT_W, WEDT_H }),
	hlbl(this, names[3], { HLBL_X, HLBL_Y, HLBL_W, HLBL_H }),
	hedt(this, TEXT("0000"), { HEDT_X, HEDT_Y, HEDT_W, HEDT_H })
{
	wnd->setOnResize(std::bind(&onResize, this, std::placeholders::_1, std::placeholders::_2));
}

void RectGroup::setUpper(LONG x, LONG y)
{
	xedt.text(_IOTA(x));
	yedt.text(_IOTA(y));
}

void RectGroup::setLower(LONG cx, LONG cy)
{
	wedt.text(_IOTA(cx));
	hedt.text(_IOTA(cy));
}