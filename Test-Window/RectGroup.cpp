#include "RectGroup.h"

RectGroup::RectGroup(Window* wnd, TSTRING title, RECT rect, TSTRING names[4])
	: GroupBox(wnd, title, rect),
	xlbl(this, names[0], { XLBL_X, XLBL_Y, XLBL_W, XLBL_H }),
	xedt(this, TEXT("0000"), { XEDT_X, XEDT_Y, XEDT_W, XEDT_H }),
	ylbl(this, names[1], { YLBL_X, YLBL_Y, YLBL_W, YLBL_H }),
	yedt(this, TEXT("0000"), { YEDT_X, YEDT_Y, YEDT_W, YEDT_H }),
	wlbl(this, names[2], { WLBL_X, WLBL_Y, WLBL_W, WLBL_H }),
	wedt(this, TEXT("0000"), { WEDT_X, WEDT_Y, WEDT_W, WEDT_H }),
	hlbl(this, names[3], { HLBL_X, HLBL_Y, HLBL_W, HLBL_H }),
	hedt(this, TEXT("0000"), { HEDT_X, HEDT_Y, HEDT_W, HEDT_H })
{}

void RectGroup::onMove(Window*, POINT p)
{
	xedt.text(_IOTA(p.x));
	yedt.text(_IOTA(p.y));
}

void RectGroup::onResize(Window*, SIZE s)
{
	wedt.text(_IOTA(s.cx));
	hedt.text(_IOTA(s.cy));
}

void RectGroup::setRect(RECT r)
{
	xedt.text(_IOTA(r.left));
	yedt.text(_IOTA(r.top));
	wedt.text(_IOTA(r.right));
	hedt.text(_IOTA(r.bottom));
}
