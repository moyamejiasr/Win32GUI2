#pragma once
#pragma warning (disable : 26495)

#include "Control.h"
#include "WndClass.h"

// Common callback definitions
typedef std::function<bool(Window*)> OnCloseFunc;
typedef std::function<void(Control*, bool)> OnFocusFunc;
typedef std::function<void(Window*, POINT)> OnResizeFunc;
typedef std::function<void(Window*, POINT)> OnMoveFunc;

class Window: public Control
{
public:
	Window(TSTRING, LONG, LONG);
	Window(TSTRING, DWORD, RECT);
	Window(Control*, TSTRING, DWORD, RECT);
protected:
	static thread_local WndClass mWClass;
	OnCloseFunc mOnClose = NULL;
	OnFocusFunc mOnFocus = NULL;
	OnResizeFunc mOnResize = NULL;
	OnMoveFunc mOnMove = NULL;
	bool mDraggable = false;
	Control* mPrevHover = NULL;
	POINT mMinSize = { 120, 80 };
	POINT mMaxSize = { 1920, 1080 };

	virtual LRESULT onDraw(HDC);
	virtual bool onClose();
	virtual void onFocus(bool);
	virtual void onResize(POINT);
	virtual void onMove(POINT);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

