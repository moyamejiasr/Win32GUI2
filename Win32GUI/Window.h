#pragma once
#pragma warning (disable : 26495)

#include "Control.h"

// Common callback definitions
typedef std::function<bool(Window*)> OnCloseFunc;
typedef std::function<void(Control*, bool)> OnFocusFunc;
typedef std::function<void(Window*, SIZE)> OnResizeFunc;
typedef std::function<void(Window*, POINT)> OnMoveFunc;

class Window: public Control
{
public:
	Window(TSTRING, LONG = 320, LONG = 240);
	Window(TSTRING, RECT);
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
	bool clipChildren();
	bool clipSiblings();
	bool composited();
	bool layered();
	bool leftScrollbar();
	bool maximizeBox();
	bool minimizeBox();
	bool focusable();
	bool sysMenu();
	bool topMost();

	void titleBar(bool);
	void resizable(bool);
	void clipChildren(bool);
	void clipSiblings(bool);
	void composited(bool);
	void layered(bool);
	void leftScrollbar(bool);
	void maximizeBox(bool);
	void minimizeBox(bool);
	void focusable(bool);
	void sysMenu(bool);
	void topMost(bool);

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

	template<class... _Types>
	void setOnClose(_Types&&...);

	template<class... _Types>
	void setOnFocus(_Types&&...);

	template<class... _Types>
	void setOnResize(_Types&&...);

	template<class... _Types>
	void setOnMove(_Types&&...);

protected:
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
	virtual void onResize(SIZE);
	virtual void onMove(POINT);
	virtual LRESULT procedure(UINT, WPARAM, LPARAM);
};

template<class ..._Types>
inline void Window::setOnClose(_Types&& ... args)
{
	mOnClose = std::bind(std::forward<_Types>(args)...,
		std::placeholders::_1);
}

template<class ..._Types>
inline void Window::setOnFocus(_Types&& ... args)
{
	mOnFocus = std::bind(std::forward<_Types>(args)...,
		std::placeholders::_1, std::placeholders::_2);
}

template<class ..._Types>
inline void Window::setOnResize(_Types&& ...args)
{
	mOnResize = std::bind(std::forward<_Types>(args)...,
		std::placeholders::_1, std::placeholders::_2);
}

template<class ..._Types>
inline void Window::setOnMove(_Types&& ...args)
{
	mOnMove = std::bind(std::forward<_Types>(args)..., 
		std::placeholders::_1, std::placeholders::_2);
}
