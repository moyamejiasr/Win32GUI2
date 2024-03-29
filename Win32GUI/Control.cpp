#include "Control.h"

thread_local int Control::wndCount = 0;
thread_local HINSTANCE Control::instance = NULL;

Control::~Control()
{
    if (!mHwnd) return;

    // Delete our own created objects
    HFONT pFont = (HFONT)SendMessage(mHwnd, WM_GETFONT, NULL, NULL);
    if (pFont != NULL) DeleteObject(pFont);

    // Prevent msgs to control with already removed vtable.
    SetControl(mHwnd, NULL);

    // Finally destroy
    DestroyWindow(mHwnd);
    mHwnd = nullptr;
}

HDC Control::hdc()
{
    return GetDC(mHwnd);
}

HWND Control::hwnd()
{
    return this->mHwnd;
}

HINSTANCE Control::hinstance()
{
    return GetWindowInstance(mHwnd);
}

Control* Control::parent()
{
    return AsControl(GetParent(this->mHwnd));
}

TSTRING Control::text()
{
    int len = GetWindowTextLength(mHwnd) + 1;
    TCHAR* buff = new TCHAR[len];
    GetWindowText(mHwnd, buff, len);
    TSTRING result = buff; delete[] buff;
    return result;
}

void Control::text(const TSTRING& text)
{
    SetWindowText(mHwnd, text.c_str());
}

SIZE Control::size()
{
    RECT it = rect();
    return { it.right, it.bottom };
}

POINT Control::position()
{
    RECT it = rect();
    return { it.left, it.top };
}

RECT Control::rect()
{
    RECT rect;
    GetWindowRect(mHwnd, &rect);
    rect.right -= rect.left, rect.bottom -= rect.top;
    return rect;
}

RECT Control::clientRect()
{
    RECT rect;
    GetClientRect(mHwnd, &rect);
    return rect;
}

bool Control::border()
{
    return style.has(WS_BORDER);
}

bool Control::hScrollbar()
{
    return style.has(WS_HSCROLL);
}

bool Control::vScrollbar()
{
    return style.has(WS_VSCROLL);
}

bool Control::clientEdge()
{
    return exstyle.has(WS_EX_CLIENTEDGE);
}

bool Control::modalFrame()
{
    return exstyle.has(WS_EX_DLGMODALFRAME);
}

bool Control::staticEdge()
{
    return exstyle.has(WS_EX_STATICEDGE);
}

void Control::border(bool state)
{
    if (state) style.add(WS_BORDER);
    else style.subs(WS_BORDER);
    UpdateStyle(mHwnd);
}

void Control::hScrollbar(bool state)
{
    if (state) style.add(WS_HSCROLL);
    else style.subs(WS_HSCROLL);
    UpdateStyle(mHwnd);
}

void Control::vScrollbar(bool state)
{
    if (state) style.add(WS_VSCROLL);
    else style.subs(WS_VSCROLL);
    UpdateStyle(mHwnd);
}

void Control::clientEdge(bool state)
{
    if (state) exstyle.add(WS_EX_CLIENTEDGE);
    else exstyle.subs(WS_EX_CLIENTEDGE);
    UpdateStyle(mHwnd);
}

void Control::modalFrame(bool state)
{
    if (state) exstyle.add(WS_EX_DLGMODALFRAME);
    else exstyle.subs(WS_EX_DLGMODALFRAME);
    UpdateStyle(mHwnd);
}

void Control::staticEdge(bool state)
{
    if (state) exstyle.add(WS_EX_STATICEDGE);
    else exstyle.subs(WS_EX_STATICEDGE);
    UpdateStyle(mHwnd);
}

void Control::size(LONG width, LONG height)
{
    size({ width, height });
}

void Control::size(const SIZE& p)
{
    SetWindowPos(mHwnd, NULL, 0, 0, p.cx, p.cy, SWP_NOMOVE | SWP_NOZORDER);
}

void Control::position(LONG width, LONG height)
{
    position({ width, height });
}

void Control::position(const POINT& p)
{
    SetWindowPos(mHwnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Control::rect(const RECT& r)
{
    SetWindowPos(mHwnd, NULL, r.left, r.top, r.right, r.bottom, SWP_NOZORDER);
}

void Control::pointRect(RECT& r)
{
    r.left = XPixFromXDU(r.left, mSzChar.cx);
    r.right = XPixFromXDU(r.right, mSzChar.cx);
    r.top = YPixFromYDU(r.top, mSzChar.cy);
    r.bottom = YPixFromYDU(r.bottom, mSzChar.cy);
    rect(r);
}

void Control::pointRect(RECT&& r)
{
    pointRect(r);
}

void Control::clientRect(RECT& r)
{
    AdjustWindowRectEx(&r, style.get(),
        GetMenu(mHwnd) == NULL, exstyle.get());
    rect(r);
}

void Control::clientRect(RECT&& r)
{
    clientRect(r);
}

bool Control::enabled()
{
    return IsWindowEnabled(mHwnd);
}

bool Control::visible()
{
    return IsWindowVisible(mHwnd);
}

void Control::enabled(bool enabled)
{
    EnableWindow(mHwnd, enabled);
    // Propagate to children
    forChildren([enabled](Control* c)->bool {
        EnableWindow(c->mHwnd, enabled); return true; });
}

void Control::visible(bool visible)
{
    ShowWindow(mHwnd, visible ? SW_SHOW : SW_HIDE);
}

COLORREF Control::backColor()
{
    return mBColor;
}

COLORREF Control::textColor()
{
    return mFColor;
}

TSTRING Control::textFont()
{
    return TSTRING(mFont.lfFaceName);
}

LONG Control::textSize()
{
    HDC hDC = hdc();
    LONG s = MulDiv(-mFont.lfHeight, 72, GetDeviceCaps(hDC, LOGPIXELSY));
    ReleaseDC(mHwnd, hDC);
    return s;
}

bool Control::textItalic()
{
    return (bool)mFont.lfItalic;
}

bool Control::textUnderline()
{
    return (bool)mFont.lfUnderline;
}

bool Control::textStrikeOut()
{
    return (bool)mFont.lfStrikeOut;
}

void Control::backColor(COLORREF color)
{
    mBColor = color;
}

void Control::textColor(COLORREF color)
{
    mFColor = color;
    redraw();
}

void Control::textFont(const TSTRING& str)
{
    size_t nLen = 32 > str.size() ? 31 : str.size();
    std::copy(str.begin(), str.end(), mFont.lfFaceName);
    mFont.lfFaceName[nLen] = '\0';
    updateFont();
}

void Control::textSize(LONG size)
{
    HDC hDC = hdc();
    mFont.lfHeight = -MulDiv(size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    ReleaseDC(mHwnd, hDC);
    updateFont();
}

void Control::textItalic(bool state)
{
    mFont.lfItalic = state;
    updateFont();
}

void Control::textUnderline(bool state)
{
    mFont.lfUnderline = state;
    updateFont();
}

void Control::textStrikeOut(bool state)
{
    mFont.lfStrikeOut = state;
    updateFont();
}

bool Control::valid()
{
    return mHwnd && IsWindow(mHwnd);
}

inline UINT Control::childCount()
{
    UINT count = 0;
    forChildren([&](Control* c)->bool {
        count++; return true; });
    return count;
}

void Control::show()
{
    visible(true);
}

void Control::hide()
{
    visible(false);
}

void Control::updateFont()
{
    // Update font
    HFONT pFont = (HFONT)SendMessage(mHwnd, WM_GETFONT, NULL, NULL);
    if (pFont != NULL) DeleteObject(pFont);
    HFONT nFont = CreateFontIndirect(&mFont);
    SendMessage(mHwnd, WM_SETFONT, (WPARAM)nFont, TRUE);

    // Get Dialog Units
    HDC dc = hdc(); SelectObject(dc, nFont);
    GetTextExtentPointW(dc, L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 52, &mSzChar);
    ReleaseDC(mHwnd, dc);
    mSzChar.cx = (mSzChar.cx / 26 + 1) / 2;

    // Finally redraw everything
    redraw();
}

void Control::redraw()
{
    InvalidateRect(mHwnd, NULL, TRUE);
}

void Control::forChildren(OnIterFunc iter)
{
    std::vector<Control*> controls;
    HWND current = FindWindowEx(this->mHwnd, NULL, NULL, NULL);
    while (current != NULL && iter(AsControl(current)))
        current = FindWindowEx(this->mHwnd, current, NULL, NULL);
}

void Control::setOnDraw(OnDrawFunc func)
{
    mOnDraw = func;
}

void Control::setOnHover(OnHoverFunc func)
{
    mOnHover = func;
}

void Control::setOnClick(OnClickFunc func)
{
    mOnClick = func;
}

void Control::setOnDoubleClick(OnDoubleClickFunc func)
{
    mOnDoubleClick = func;
}

void Control::setOnMouseWheel(OnMouseWheelFunc func)
{
    mOnMouseWheel = func;
}

BOOL Control::join()
{
    MSG msg;
    BOOL result;
    while ((result = GetMessage(&msg, NULL, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return result;
}

TSTRING Control::lastError()
{
    DWORD error = GetLastError();
    if (!error) return TSTRING();
    LPTSTR buffer = nullptr;
    size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, NULL);
    TSTRING result(buffer, size);
    LocalFree(buffer);
    return result;
}

Control::Control(Control* parent, PCTSTR type, PCTSTR text, DWORD style, const PRECT rect)
{
    // Setup text data
    if (parent)
    {
        // Inherit from parent
        mFont = parent->mFont;
        mFColor = parent->mFColor; mBColor = parent->mBColor;
    }
    else
    {
        // Use system parameters
        NONCLIENTMETRICS metrics{ sizeof(NONCLIENTMETRICS) };
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);
        mFont = metrics.lfMessageFont;
        mBColor = GetSysColor(COLOR_3DFACE); mFColor = GetSysColor(COLOR_WINDOWTEXT);
    }

    // Create window
    // According to the documentation, every coordinate
    // set here is screen-based.
    mHwnd = CreateWindow(type, text, style,
        rect->left, rect->top, rect->right, rect->bottom,
        parent ? parent->mHwnd : NULL,
        0 /* No ID. No need */, instance, NULL);
    if (!mHwnd)
    {
#ifdef _DEBUG
        STDOUT << lastError() << std::endl;
#endif // _DEBUG
        return;
    }

    // Update window data
    SetControl(mHwnd, this);
    updateFont();
    // Update function last.
    // It invokes the procedure and may fail
    // if control has not been set already.
}

LRESULT Control::onDraw(HDC hdc)
{
    if (mOnDraw)
        return mOnDraw(this, hdc);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, mFColor);
    SetDCBrushColor(hdc, mBColor);
    return (LRESULT)GetStockObject(DC_BRUSH);
}

void Control::onHover(bool state)
{
    if (mOnHover)
        mOnHover(this, state);
}

void Control::onClick(DWORD keys, POINT point)
{
    if (mOnClick)
        mOnClick(this, keys, point);
}

void Control::onDoubleClick(DWORD keys, POINT point)
{
    if (mOnDoubleClick)
        mOnDoubleClick(this, keys, point);
}

void Control::onMouseWheel(DWORD value, POINT point)
{
    if (mOnMouseWheel)
        mOnMouseWheel(this, value, point);
}

LRESULT Control::procedure(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Default-handle unhandled messages like WM_CANCELMODE.
    // Most happen before the Window constructor returns or after
    // the destructor gets called, as the class vtable is not set.
    return DefWindowProc(this->mHwnd, uMsg, wParam, lParam);
}

DWORD Control::Style::get()
{
    return GetWindowLong(mOuter->mHwnd, mType);
}

bool Control::Style::has(DWORD f)
{
    return get() & f;
}

void Control::Style::add(DWORD f)
{
    SetWindowLongPtr(mOuter->mHwnd, mType, get() | f);
}

void Control::Style::subs(DWORD f)
{
    SetWindowLongPtr(mOuter->mHwnd, mType, get() & ~f);
}
