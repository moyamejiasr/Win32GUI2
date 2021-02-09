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
	if (enableCheck)
	{
		setb.setOnClick([&](Control*, DWORD, POINT)->void { 
			RECT r{
				std::stoi(xedt.text()),
				std::stoi(yedt.text()),
				std::stoi(wedt.text()) + r.left,
				std::stoi(hedt.text()) + r.top,
			};
			if (chec.checked())
			{
				wnd->newMessageBox(L"Setting rect as client area");
				wnd->clientRect(r);
			}
			else
			{
				wnd->newMessageBox(L"Setting rect as non-client area");
				wnd->rect(r);
			}
			});
	}
	else
	{
		chec.enabled(false);
		setb.setOnClick([&](Control*, DWORD, POINT)->void {
			wnd->newMessageBox(L"Setting min/max properties");
			wnd->minSize(std::stoi(xedt.text()), std::stoi(yedt.text()));
			wnd->maxSize(std::stoi(wedt.text()), std::stoi(hedt.text()));
			});
	}
}

void RectGroup::onMove(Window*, POINT p)
{
	xedt.text(_IOTA(p.x));
	yedt.text(_IOTA(p.y));
}

void RectGroup::onResize(Window*, SIZE s)
{
	if (!chec.checked())
	{
		RECT r = wnd->rect();
		s.cx = r.right - r.left; s.cy = r.bottom - r.top;
	}
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
