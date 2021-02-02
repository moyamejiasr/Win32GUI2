#include "Window.h"

thread_local WndClass Window::mWClass(Window::WndProc, 
    _IOTA(GetCurrentThreadId()));

Window::Window(TSTRING text, LONG width, LONG height)
    :Window(text, WS_OVERLAPPEDWINDOW,
        { CW_USEDEFAULT, CW_USEDEFAULT, width, height })
{}

Window::Window(TSTRING text, DWORD style, RECT rect)
    :Control(mWClass.instance(), mWClass.name(), 
        text.c_str(), style, rect)
{}

Window::Window(Control* parent, TSTRING text, DWORD style, RECT rect)
    :Control(parent, mWClass.name(), text.c_str(), 
        style + WS_CHILD, rect)
{}

LRESULT Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* it = (Window*)AsControl(hwnd);
	if (!it) // Not a valid control (UserData not set??)
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize = it->mMinSize;
		lpMMI->ptMaxTrackSize = it->mMaxSize;
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
			LRESULT hit = DefWindowProc(it->mHwnd, uMsg, wParam, lParam);
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
