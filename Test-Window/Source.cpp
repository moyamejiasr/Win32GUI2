#include "../Win32GUI/Manager.h"
#include "RectGroup.h"

//
// Main Window
//
SIZE min = { 120, 80 }, max = { 1920, 1080 };
Window window(TEXT("Test-Window"), 800, 600);

//
// Client-Rect GroupBox
//
const int RECT_X = 12,						RECT_Y = 12;
const int RECT_W = HEDT_X + HEDT_W + 12,	RECT_H = SETB_Y + SETB_H + 12;
TSTRING rectNames[4] = { TEXT("XPos"), TEXT("YPos"), TEXT("WSiz"), TEXT("XPos") };

RectGroup rect(&window, TEXT("Window Rectangle"), 
	{ RECT_X, RECT_Y, RECT_W, RECT_H }, rectNames, true);

//
// Min-Max GroupBox
//
const int MIMA_X = RECT_X + RECT_W + 12,	MIMA_Y = 12;
const int MIMA_W = 176,						MIMA_H = SETB_Y + SETB_H + 12;
TSTRING mimaNames[4] = { TEXT("WMin"), TEXT("HMin"), TEXT("WMax"), TEXT("HMax") };

RectGroup mima(&window, TEXT("Window Min/Max Size"), 
	{ MIMA_X, MIMA_Y, MIMA_W, MIMA_H }, mimaNames, false);

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
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	window.setOnClose([&](Window*)->bool {
		return window.newMessageBox(L"Do you want to close?", MB_OKCANCEL) == 1; });
	window.minSize(min.cx, min.cy);
	window.maxSize(max.cx, max.cy);

	// RECT
	// Function members callback
	using namespace std::placeholders;
	window.setOnMove(std::bind(&RectGroup::onMove, &rect, _1, _2));
	window.setOnResize(std::bind(&RectGroup::onResize, &rect, _1, _2));

	// MIMA
	mima.setMinMax(min, max);

	// Buttons
	// Lambda callbacks
	maxw.setOnClick([&](Control*, DWORD, POINT)->void { window.maximize(); });
	minw.setOnClick([&](Control*, DWORD, POINT)->void { window.minimize(); });
	resw.setOnClick([&](Control*, DWORD, POINT)->void { window.restore(); });

	window.show();

	Control::join();
	return 0;
}