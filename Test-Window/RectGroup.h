#pragma once
#include "../Win32GUI/Manager.h"

#define FONT_WIDTH 9

//	-	Child X label
const int XLBL_X = FONT_WIDTH,				XLBL_Y = FONT_WIDTH * 2 + 5;
const int XLBL_W = FONT_WIDTH * 4,			XLBL_H = 23;
//	-	Child X edit
const int XEDT_X = XLBL_X + XLBL_W,			XEDT_Y = FONT_WIDTH * 2;
const int XEDT_W = FONT_WIDTH * 4,			XEDT_H = XLBL_H;

//	-	Child Y label
const int YLBL_X = XEDT_X + XEDT_W + 12,	YLBL_Y = FONT_WIDTH * 2 + 5;
const int YLBL_W = FONT_WIDTH * 4,			YLBL_H = 23;
//	-	Child Y edit
const int YEDT_X = YLBL_X + XLBL_W,			YEDT_Y = FONT_WIDTH * 2;
const int YEDT_W = FONT_WIDTH * 4,			YEDT_H = YLBL_H;

//	-	Child W label
const int WLBL_X = FONT_WIDTH,				WLBL_Y = XLBL_Y + XLBL_H + 12;
const int WLBL_W = FONT_WIDTH * 4,			WLBL_H = 23;
//	-	Child W edit
const int WEDT_X = WLBL_X + WLBL_W,			WEDT_Y = XEDT_Y + XEDT_H + 12;
const int WEDT_W = FONT_WIDTH * 4,			WEDT_H = XLBL_H;

//	-	Child H label
const int HLBL_X = WEDT_X + WEDT_W + 12,	HLBL_Y = YLBL_Y + YLBL_H + 12;
const int HLBL_W = FONT_WIDTH * 4,			HLBL_H = 23;
//	-	Child H edit
const int HEDT_X = HLBL_X + HLBL_W,			HEDT_Y = YEDT_Y + YEDT_H + 12;
const int HEDT_W = FONT_WIDTH * 4,			HEDT_H = YLBL_H;

//	-	Child Set Button
const int SETB_W = 75,						SETB_H = 23;
const int SETB_X = HEDT_X + HEDT_W - SETB_W,SETB_Y = HEDT_Y + HEDT_H + 12;
//	-	Child Type CheckBox
const int CHEC_X = WLBL_X,					CHEC_Y = SETB_Y;
const int CHEC_W = SETB_X - CHEC_X - 12,	CHEC_H = 23;
class RectGroup: GroupBox
{
public:
	RectGroup(Window*, TSTRING, RECT, TSTRING[4], bool);
	void onMove(Window*, POINT);
	void onResize(Window*, SIZE);
	void setRect(RECT);

protected:
	Window* wnd;
	TextView xlbl; EditText xedt;
	TextView ylbl; EditText yedt;
	TextView wlbl; EditText wedt;
	TextView hlbl; EditText hedt;
	Button setb; CheckBox chec;
};

