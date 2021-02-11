#include "Window.h"

thread_local ATOM Window::cName = initialize();

Window::Window(TSTRING text, LONG width, LONG height)
    :Window(text, { CW_USEDEFAULT, CW_USEDEFAULT, width, height })
{}

Window::Window(TSTRING text, RECT rect)
	: Window(NULL, text, WS_OVERLAPPEDWINDOW, rect)
{}

Window::Window(Control* parent, TSTRING text, DWORD style, RECT rect)
    :Control(parent, MAKEINTATOM(cName), text.c_str(),
        parent ? style | WS_CHILD : style, &rect)
{}

POINT Window::minSize()
{
	return mMinSize;
}

POINT Window::maxSize()
{
	return mMaxSize;
}

void Window::minSize(POINT size)
{
	mMinSize = size;
}

void Window::minSize(LONG width, LONG height)
{
	minSize({ width, height });
}

void Window::maxSize(POINT size)
{
	mMaxSize = size;
}

void Window::maxSize(LONG width, LONG height)
{
	maxSize({ width, height });
}

bool Window::titleBar()
{
	return style.has(WS_CAPTION);
}

bool Window::resizable()
{
	return style.has(WS_THICKFRAME);
}

bool Window::clipChildren()
{
	return style.has(WS_CLIPCHILDREN);
}

bool Window::clipSiblings()
{
	return style.has(WS_CLIPSIBLINGS);
}

bool Window::composited()
{
	return exstyle.has(WS_EX_COMPOSITED);
}

bool Window::layered()
{
	return exstyle.has(WS_EX_LAYERED);
}

bool Window::leftScrollbar()
{
	return exstyle.has(WS_EX_LEFTSCROLLBAR);
}

bool Window::maximizeBox()
{
	return style.has(WS_MAXIMIZEBOX);
}

bool Window::minimizeBox()
{
	return style.has(WS_MINIMIZEBOX);
}

bool Window::focusable()
{
	return exstyle.has(WS_EX_NOACTIVATE);
}

bool Window::sysMenu()
{
	return style.has(WS_SYSMENU);
}

bool Window::topMost()
{
	return exstyle.has(WS_EX_TOPMOST);
}

void Window::titleBar(bool state)
{
	if (state) style.add(WS_CAPTION);
	else style.subs(WS_CAPTION);
}

void Window::resizable(bool state)
{
	if (state) style.add(WS_THICKFRAME);
	else style.subs(WS_THICKFRAME);
}

void Window::clipChildren(bool state)
{
	if (state) style.add(WS_CLIPCHILDREN);
	else style.subs(WS_CLIPCHILDREN);
}

void Window::clipSiblings(bool state)
{
	if (state) style.add(WS_CLIPSIBLINGS);
	else style.subs(WS_CLIPSIBLINGS);
}

void Window::composited(bool state)
{
	if (state) exstyle.add(WS_EX_COMPOSITED);
	else style.subs(WS_EX_COMPOSITED);
}

void Window::layered(bool state)
{
	if (state) exstyle.add(WS_EX_LAYERED);
	else exstyle.subs(WS_EX_LAYERED);
}

void Window::leftScrollbar(bool state)
{
	if (state) exstyle.add(WS_EX_LEFTSCROLLBAR);
	else exstyle.subs(WS_EX_LEFTSCROLLBAR);
}

void Window::maximizeBox(bool state)
{
	if (state) style.add(WS_MAXIMIZEBOX);
	else style.subs(WS_MAXIMIZEBOX);
}

void Window::minimizeBox(bool state)
{
	if (state) style.add(WS_MINIMIZEBOX);
	else style.subs(WS_MINIMIZEBOX);
}

void Window::focusable(bool state)
{
	if (state) exstyle.add(WS_EX_NOACTIVATE);
	else exstyle.subs(WS_EX_NOACTIVATE);
}

void Window::sysMenu(bool state)
{
	if (state) style.add(WS_SYSMENU);
	else style.subs(WS_SYSMENU);
}

void Window::topMost(bool state)
{
	HWND flag = HWND_NOTOPMOST;
	if (state)
		flag = HWND_TOPMOST;
	SetWindowPos(mHwnd, flag, 0, 0, 0, 
		0, SWP_NOMOVE | SWP_NOSIZE);
}

bool Window::appWindow()
{
	return exstyle.has(WS_EX_APPWINDOW);
}

bool Window::draggable()
{
	return mDraggable;
}

void Window::appWindow(bool state)
{
	if (state) exstyle.add(WS_EX_APPWINDOW);
	else exstyle.subs(WS_EX_APPWINDOW);
}

void Window::draggable(bool state)
{
	mDraggable = state;
}

bool Window::contextHelp()
{
	return exstyle.has(WS_EX_CONTEXTHELP);
}

bool Window::controlParent()
{
	return exstyle.has(WS_EX_CONTROLPARENT);
}

bool Window::maximized()
{
	WINDOWPLACEMENT plmnt = { 0 };
	plmnt.length = sizeof(plmnt);
	GetWindowPlacement(mHwnd, &plmnt);
	return plmnt.showCmd & SW_MAXIMIZE;
}

bool Window::minimized()
{
	WINDOWPLACEMENT plmnt = { 0 };
	plmnt.length = sizeof(plmnt);
	GetWindowPlacement(mHwnd, &plmnt);
	return plmnt.showCmd & SW_MINIMIZE;
}

void Window::contextHelp(bool state)
{
	if (state) exstyle.add(WS_EX_CONTEXTHELP);
	else exstyle.subs(WS_EX_CONTEXTHELP);
}

void Window::controlParent(bool state)
{
	if (state) exstyle.add(WS_EX_CONTROLPARENT);
	else exstyle.subs(WS_EX_CONTROLPARENT);
}

void Window::maximize()
{
	ShowWindow(mHwnd, SW_MAXIMIZE);
}

void Window::minimize()
{
	ShowWindow(mHwnd, SW_MINIMIZE);
}

void Window::restore()
{
	ShowWindow(mHwnd, SW_RESTORE);
}

void Window::redrawMenu()
{
	DrawMenuBar(mHwnd);
}

int Window::newMessageBox(TSTRING text, UINT flags)
{
	return MessageBox(mHwnd, text.c_str(), this->text().c_str(), flags);
}

void Window::setOnClose(OnCloseFunc func)
{
	mOnClose = func;
}

void Window::setOnFocus(OnFocusFunc func)
{
	mOnFocus = func;
}

void Window::setOnResize(OnResizeFunc func)
{
	mOnResize = func;
}

void Window::setOnMove(OnMoveFunc func)
{
	mOnMove = func;
}

LRESULT Window::onDraw(HDC hdc)
{
	if (mOnDraw)
		return mOnDraw(this, hdc);
	RECT rect;
	GetClientRect(mHwnd, &rect);
	SetDCBrushColor(hdc, mBColor);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(DC_BRUSH));
	return TRUE;
}

bool Window::onClose()
{
	// Close if callback not exists
	// also if it returned true.
	return !mOnClose || mOnClose(this);
}

void Window::onFocus(bool state)
{
	if (mOnFocus)
		mOnFocus(this, state);
}

void Window::onResize(SIZE point)
{
	if (mOnResize)
		mOnResize(this, point);
}

void Window::onMove(POINT point)
{
	if (mOnMove)
		mOnMove(this, point);
}

ATOM Window::initialize()
{
	WNDCLASS wndClass{ CS_DBLCLKS, MainWndProc,
		0, 0, instance = GetModuleHandle(NULL) };

	// Use thread as name to prevent collisions
	TSTRING name = _IOTA(GetCurrentThreadId());
	wndClass.lpszClassName = name.c_str();
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);

	// Return atom for usage
	return RegisterClass(&wndClass);
}

LRESULT Window::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Keep a list of active child windows to end
	// the loop once all of them get destroyed.
	switch (uMsg) {
	case WM_CREATE: wndCount++; break;
	case WM_DESTROY: wndCount--;
		// Check if no more windows active
		if (!wndCount) PostQuitMessage(0);
		break;
	}

	// Will fail until ptr set in constructor
	Window* it = (Window*)AsControl(hwnd);
	if (!it) return DefWindowProc(hwnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize = it->mMinSize;
		lpMMI->ptMaxTrackSize = it->mMaxSize;
		break;
	}
	case WM_SIZE:
		it->onResize(LPARAM2POINT(lParam));
		break;
	case WM_MOVE:
		it->onMove(LPARAM2POINT(lParam));
		break;
	case WM_NCHITTEST:
		if (it->mDraggable)
		{
			LRESULT hit = DefWindowProc(hwnd, uMsg, wParam, lParam);
			if (GetAsyncKeyState(VK_LBUTTON) & VK_LBUTTON && hit == HTCLIENT)
				return HTCAPTION;
		}
		break;
	case WM_ACTIVATE:
		// WA_INACTIVE value is 0
		it->onFocus(LOWORD(wParam));
		break;
	case WM_SETCURSOR:
	{
		if (it->mPrevHover)
		{
			// Return if hovered control is the same
			if (it->mPrevHover->mHwnd == (HWND)wParam)
				break;
			// Exit hover if exists and changed
			if (it->mPrevHover)
				it->mPrevHover->onHover(false);
		}
		// Enter new one
		it->mPrevHover = AsControl((HWND)wParam);
		if (it->mPrevHover) it->mPrevHover->onHover(true);
		break;
	}
	case WM_COMMAND:
	{
		Control* control = AsControl((HWND)lParam);
		if (control) return control->procedure(uMsg, wParam, lParam);
		// Is it a context-menu item?? TODO: Implement
		//else if (HIWORD(wParam) == 0)
		break;
	}
	case WM_PARENTNOTIFY:
		break;
	case WM_MOUSEWHEEL:
		// All controls except Buttons trigger this message
		// Do not send if control is disabled
		if (it->mPrevHover && it->mPrevHover->enabled())
			it->mPrevHover->onMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam), LPARAM2POINT(lParam));
		return 0;
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
		// All controls except Buttons trigger this message
		// Do not send if control is disabled
		if (it->mPrevHover && it->mPrevHover->enabled())
			it->mPrevHover->onDoubleClick(uMsg, LPARAM2POINT(lParam));
		return 0;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN:
		// All controls except Buttons trigger this message
		// Do not send if control is disabled
		if (it->mPrevHover && it->mPrevHover->enabled())
			it->mPrevHover->onClick(uMsg, LPARAM2POINT(lParam));
		return 0;
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORLISTBOX:
	{
		Control* control = AsControl((HWND)lParam);
		if (control) return control->onDraw((HDC)wParam);
		break; // Not owned by us, continue with default.
	}
	case WM_ERASEBKGND:
		return it->onDraw((HDC)(wParam));
	case WM_CLOSE:
		if (it->onClose()) it->~Window();
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}