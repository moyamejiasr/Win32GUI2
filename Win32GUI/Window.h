#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

// Common callback definitions
typedef std::function<bool(Window*)> OnCloseFunc;
typedef std::function<void(Control*, bool)> OnFocusFunc;
typedef std::function<void(Window*, POINT)> OnResizeFunc;
typedef std::function<void(Window*, POINT)> OnMoveFunc;

class Window: public Control
{
public:
	Window(TSTRING, LONG = 320, LONG = 240);
	Window(TSTRING, DWORD, RECT);
	Window(Control*, TSTRING, DWORD, RECT);

	////////////////////////////////////////////////////////////
	// Window: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No common properties */

	////////////////////////////////////////////////////////////
	// Rectangle: Getters & Setters
	////////////////////////////////////////////////////////////

	POINT minSize();
	POINT maxSize();
	void minSize(POINT);
	void minSize(LONG, LONG);
	void maxSize(POINT);
	void maxSize(LONG, LONG);

	////////////////////////////////////////////////////////////
	// Appearance: Getters & Setters
	////////////////////////////////////////////////////////////

	bool titleBar();
	bool resizable();
	bool clientEdge();
	bool clipChildren();
	bool clipSiblings();
	bool composited();
	bool hScrollbar();
	bool vScrollbar();
	bool layered();
	bool layoutRTL();
	bool readingRTL();
	bool leftScrollbar();
	bool maximizeBox();
	bool minimizeBox();
	bool focusable();
	bool staticEdge();
	bool sysMenu();
	bool topMost();
	bool transparent();

	void titleBar(bool);
	void resizable(bool);
	void clientEdge(bool);
	void clipChildren(bool);
	void clipSiblings(bool);
	void composited(bool);
	void hScrollbar(bool);
	void vScrollbar(bool);
	void layered(bool);
	void layoutRTL(bool);
	void readingRTL(bool);
	void leftScrollbar(bool);
	void maximizeBox(bool);
	void minimizeBox(bool);
	void focusable(bool);
	void staticEdge(bool);
	void sysMenu(bool);
	void topMost(bool);
	void transparent(bool);

	////////////////////////////////////////////////////////////
	// Behavior: Getters & Setters
	////////////////////////////////////////////////////////////

	bool appWindow();
	bool draggable();

	void appWindow(bool);
	void draggable(bool);

	////////////////////////////////////////////////////////////
	// Misc: Getters, Setters & Functions
	////////////////////////////////////////////////////////////

	bool contextHelp();
	bool controlParent();
	bool maximized();
	bool minimized();

	void contextHelp(bool);
	void controlParent(bool);
	void maximize();
	void minimize();
	void restore();

	void redrawMenu();
	int newMessageBox(TSTRING, UINT = MB_ICONINFORMATION);
	void setOnClose(OnCloseFunc);
	void setOnFocus(OnFocusFunc);
	void setOnResize(OnResizeFunc);
	void setOnMove(OnMoveFunc);

protected:
	OnCloseFunc mOnClose = NULL;
	OnFocusFunc mOnFocus = NULL;
	OnResizeFunc mOnResize = NULL;
	OnMoveFunc mOnMove = NULL;
	bool mDraggable = false;
	Control* mPrevHover = NULL;
	POINT mMinSize = { 120, 80 };
	POINT mMaxSize = { 1920, 1080 };

	static thread_local WndClass mWClass;
	virtual LRESULT onDraw(HDC);
	virtual bool onClose();
	virtual void onFocus(bool);
	virtual void onResize(POINT);
	virtual void onMove(POINT);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

