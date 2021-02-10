#include "RectGroup.h"

RectGroup::RectGroup(Window* wnd, TSTRING title, RECT rect, TSTRING names[4], bool enableCheck)
	: GroupBox(wnd, title, rect),
	xlbl(this, names[0], { XLBL_X, XLBL_Y, XLBL_W, XLBL_H }),
	xedt(this, TEXT("0000"), { XEDT_X, XEDT_Y, XEDT_W, XEDT_H }),
	ylbl(this, names[1], { YLBL_X, YLBL_Y, YLBL_W, YLBL_H }),
	yedt(this, TEXT("0000"), { YEDT_X, YEDT_Y, YEDT_W, YEDT_H }),
	wlbl(this, names[2], { WLBL_X, WLBL_Y, WLBL_W, WLBL_H }),
	wedt(this, TEXT("0000"), { WEDT_X, WEDT_Y, WEDT_W, WEDT_H }),
	hlbl(this, names[3], { HLBL_X, HLBL_Y, HLBL_W, HLBL_H }),
	hedt(this, TEXT("0000"), { HEDT_X, HEDT_Y, HEDT_W, HEDT_H }),
	setb(this, TEXT("SET"), { SETB_X, SETB_Y, SETB_W, SETB_H }),
	chec(this, TEXT("As client"), { CHEC_X, CHEC_Y, CHEC_W, CHEC_H })
{
	this->wnd = wnd;
	using namespace std::placeholders;
	if (enableCheck)
		chec.setOnCheckedChange(std::bind(&RectGroup::onCheckedChange, this, _1, _2));
	else chec.enabled(false);
}

RECT RectGroup::getRect()
{
	return {std::stoi(xedt.text()), std::stoi(yedt.text()),
		std::stoi(wedt.text()), std::stoi(hedt.text())};
}

void RectGroup::onMove(Window*, POINT p)
{
	if (clientRect)
		p = { 0, 0 }; // Client-rect starts at 0
	xedt.text(_IOTA(p.x));
	yedt.text(_IOTA(p.y));
}

void RectGroup::onResize(Window*, SIZE s)
{
	if (!clientRect)
	{
		RECT r = wnd->rect();
		s.cx = r.right; s.cy = r.bottom;
	}
	wedt.text(_IOTA(s.cx));
	hedt.text(_IOTA(s.cy));
}

void RectGroup::onCheckedChange(Control*, bool state)
{
	RECT r = wnd->rect();
	if (clientRect = state)
	{
		r = wnd->clientRect();
	}
	onMove(NULL, { r.left, r.top });
	onResize(NULL, { r.right, r.bottom });
}

void RectGroup::setMinMax(SIZE m, SIZE M)
{
	xedt.text(_IOTA(m.cx));
	yedt.text(_IOTA(m.cy));
	wedt.text(_IOTA(M.cx));
	hedt.text(_IOTA(M.cy));
}
