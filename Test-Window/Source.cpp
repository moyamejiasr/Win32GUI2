#include "../Win32GUI/Manager.h"
#include "RectGroup.h"

/*
Main Window
*/
Window window(TEXT("Test-Window"));

/*
Client-Rect GroupBox
*/
TSTRING rectNames[4] = { TEXT("XPos"), TEXT("YPos"), TEXT("WSiz"), TEXT("XPos") };
RectGroup rect(&window, TEXT("Window Rectangle"), rectNames);

/*
Min-Max GroupBox
*/
TSTRING mimaNames[4] = { TEXT("Wmin"), TEXT("Hmin"), TEXT("WMAX"), TEXT("HMAX") };
RectGroup mima(&window, TEXT("Window Min/Max Size"), mimaNames);

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

int main() {
	window.setOnMove([&](Control*, POINT p)->void { rect.setUpper(p.x, p.y); });
	window.setOnResize([&](Control*, SIZE s)->void { rect.setLower(s.cx, s.cy); });

	maxw.setOnClick([&](Control*, DWORD, POINT)->void { window.maximize(); });
	minw.setOnClick([&](Control*, DWORD, POINT)->void { window.minimize(); });
	resw.setOnClick([&](Control*, DWORD, POINT)->void { window.restore(); });

	window.show();

	Control::join();
	return 0;
}