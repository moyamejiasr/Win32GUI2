#include "../Win32GUI/Manager.h"

#define FONT_WIDTH 9

/*
Main Window
*/
Window window(TEXT("Test-Window"));

/*
Rect GroupBox
*/
#define RECT_X 12
#define RECT_Y 12
#define RECT_W 176
#define RECT_H FONT_WIDTH * 3 + 23 * 2 + 12
GroupBox rect(&window, TEXT("Window RECT"), 
	{ RECT_X, RECT_Y, RECT_W, RECT_H });

#define XLBL_X FONT_WIDTH
#define XLBL_Y FONT_WIDTH * 2 + 5
#define XLBL_W FONT_WIDTH * 4
#define XLBL_H 23
TextView xlbl(&rect, TEXT("XPos"), 
	{ XLBL_X, XLBL_Y, XLBL_W, XLBL_H });
#define XEDT_X XLBL_X + XLBL_W
#define XEDT_Y FONT_WIDTH * 2
#define XEDT_W FONT_WIDTH * 4
#define XEDT_H XLBL_H
EditText xedt(&rect, TEXT("0000"), 
	{ XEDT_X, XEDT_Y, XEDT_W, XEDT_H });

#define YLBL_X XEDT_X + XEDT_W + 12
#define YLBL_Y FONT_WIDTH * 2 + 5
#define YLBL_W FONT_WIDTH * 4
#define YLBL_H 23
TextView ylbl(&rect, TEXT("YPos"), 
	{ YLBL_X, YLBL_Y, YLBL_W, YLBL_H });
#define YEDT_X YLBL_X + XLBL_W
#define YEDT_Y FONT_WIDTH * 2
#define YEDT_W FONT_WIDTH * 4
#define YEDT_H YLBL_H
EditText yedt(&rect, TEXT("0000"), 
	{ YEDT_X, YEDT_Y, YEDT_W, YEDT_H });

#define WLBL_X FONT_WIDTH
#define WLBL_Y XLBL_Y + XLBL_H + 12
#define WLBL_W FONT_WIDTH * 4
#define WLBL_H 23
TextView wlbl(&rect, TEXT("WSiz"),
	{ WLBL_X, WLBL_Y, WLBL_W, WLBL_H });
#define WEDT_X WLBL_X + WLBL_W
#define WEDT_Y XEDT_Y + XEDT_H + 12
#define WEDT_W FONT_WIDTH * 4
#define WEDT_H XLBL_H
EditText wedt(&rect, TEXT("0000"),
	{ WEDT_X, WEDT_Y, WEDT_W, WEDT_H });

#define HLBL_X WEDT_X + WEDT_W + 12
#define HLBL_Y YLBL_Y + YLBL_H + 12
#define HLBL_W FONT_WIDTH * 4
#define HLBL_H 23
TextView hlbl(&rect, TEXT("HSiz"),
	{ HLBL_X, HLBL_Y, HLBL_W, HLBL_H });
#define HEDT_X HLBL_X + HLBL_W
#define HEDT_Y YEDT_Y + YEDT_H + 12
#define HEDT_W FONT_WIDTH * 4
#define HEDT_H YLBL_H
EditText hedt(&rect, TEXT("0000"),
	{ HEDT_X, HEDT_Y, HEDT_W, HEDT_H });

/*
Simple-action buttons
*/
#define MAXB_X 12
#define MAXB_Y RECT_Y + RECT_H + 12
#define MAXB_W 75
#define MAXB_H 23
Button maxw(&window, TEXT("Maximize"),
	{ MAXB_X, MAXB_Y, MAXB_W, MAXB_H });
#define MINB_X MAXB_X + MAXB_W + 12
#define MINB_Y MAXB_Y
#define MINB_W 75
#define MINB_H 23
Button minw(&window, TEXT("Minimize"),
	{ MINB_X, MINB_Y, MINB_W, MINB_H });
#define RESB_X MINB_X + MINB_W + 12
#define RESB_Y MINB_Y
#define RESB_W 75
#define RESB_H 23
Button resw(&window, TEXT("Restore"),
	{ RESB_X, RESB_Y, RESB_W, RESB_H });

void onMove(Window*, POINT p) {
	xedt.text(_IOTA(p.x));
	yedt.text(_IOTA(p.y));
}

void onResize(Window*, SIZE p) {
	wedt.text(_IOTA(p.cx));
	hedt.text(_IOTA(p.cy));
}

int main() {
	window.setOnMove(onMove);
	window.setOnResize(onResize);

	maxw.setOnClick([&](Control*, DWORD, POINT)->void { window.maximize(); });
	minw.setOnClick([&](Control*, DWORD, POINT)->void { window.minimize(); });
	resw.setOnClick([&](Control*, DWORD, POINT)->void { window.restore(); });

	window.show();

	Control::join();
	return 0;
}