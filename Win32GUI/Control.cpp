#include "Control.h"

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

void Control::text(TSTRING text)
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
    return rect;
}

RECT Control::clientRect()
{
    RECT rect;
    GetClientRect(mHwnd, &rect);
    return rect;
}

void Control::size(LONG width, LONG height)
{
    size(SIZE{ width, height });
}

void Control::size(SIZE p)
{
    SetWindowPos(mHwnd, NULL, 0, 0, p.cx, p.cy, SWP_NOMOVE);
}

void Control::position(LONG width, LONG height)
{
    size(SIZE{ width, height });
}

void Control::position(POINT p)
{
    SetWindowPos(mHwnd, NULL, p.x, p.y, 0, 0, SWP_NOSIZE);
}

void Control::rect(RECT r)
{
    SetWindowPos(mHwnd, NULL, r.left, r.top, r.right, r.bottom, NULL);
}

void Control::clientRect(RECT r)
{
    // Adjust rect from client to total.
    // Ignore X64 cast errors because we only want to 
    // check if a menu is present.
    // TODO: Use better menu checker
    AdjustWindowRectEx(&r, style.get(),
        reinterpret_cast<BOOL>(GetMenu(mHwnd)), exstyle.get());
    rect(r);
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
    return mFont.lfHeight;
}

bool Control::textItalic()
{
    return mFont.lfItalic;
}

bool Control::textUnderline()
{
    return mFont.lfUnderline;
}

bool Control::textStrikeOut()
{
    return mFont.lfStrikeOut;
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

void Control::textFont(TSTRING str)
{
    size_t nLen = 32 > str.size() ? 31 : str.size();
    std::copy(str.begin(), str.end(), mFont.lfFaceName);
    mFont.lfFaceName[nLen] = '\0';
    updateFont();
}

void Control::textSize(LONG size)
{
    mFont.lfHeight = size;
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

inline void Control::show()
{
    visible(true);
}

inline void Control::hide()
{
    visible(false);
}

void Control::updateFont()
{
    HFONT pFont = (HFONT)SendMessage(mHwnd, WM_GETFONT, NULL, NULL);
    if (pFont != NULL) DeleteObject(pFont);
    HFONT nFont = CreateFontIndirect(&mFont);
    SendMessage(mHwnd, WM_SETFONT, (WPARAM)nFont, TRUE);
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

Control::~Control()
{
    if (!mHwnd) return;
    HFONT pFont = (HFONT)SendMessage(mHwnd, WM_GETFONT, NULL, NULL);
    if (pFont != NULL) DeleteObject(pFont);
    DestroyWindow(mHwnd);
    mHwnd = nullptr;
}

Control::Control(HINSTANCE instance, PCTSTR type, PCTSTR text, DWORD style, RECT rect)
{
    // Setup text data
    // Use system parameters
    NONCLIENTMETRICS metrics{ sizeof(NONCLIENTMETRICS) };
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);
    mFont = metrics.lfMessageFont;
    mBColor = GetSysColor(COLOR_3DFACE); mFColor = GetSysColor(COLOR_WINDOWTEXT);

    // Create window
    mHwnd = CreateWindowEx(NULL, type, text, style,
        rect.left, rect.top, rect.right, rect.bottom,
        NULL, NULL, instance, NULL);
    if (!mHwnd) exit(-2);

    // Update window data
    SetControl(mHwnd, this);
    updateFont(); 
    // Update function last.
    // It invokes the procedure and may fail
    // if control has not been set already.
}

Control::Control(Control* parent, PCTSTR type, PCTSTR text, DWORD style, RECT rect)
{
    // Setup text data
    // Inherit from parent
    mFont = parent->mFont;
    mFColor = parent->mFColor; mBColor = parent->mBColor;

    // Create window
    mHwnd = CreateWindowEx(NULL, type, text, style,
        rect.left, rect.top, rect.right, rect.bottom,
        parent->mHwnd, (HMENU)GetTickCount(), // Use ticks as id
        parent->hinstance(), NULL);
    if (!mHwnd) exit(-2);

    // Update window data
    SetControl(mHwnd, this);
    updateFont();
    // Update function last.
    // It invokes the procedure and may fail
    // if control has not been set already.
}

LRESULT Control::onDraw(HDC hdc)
{
    // Invoke default behavior
    return FALSE;
}

void Control::onHover(bool state)
{
    if (mOnHover) mOnHover(this, state);
}

void Control::onClick(DWORD keys, POINT point)
{
    if (mOnClick) mOnClick(this, keys, point);
}

void Control::onDoubleClick(DWORD keys, POINT point)
{
    if (mOnDoubleClick) mOnDoubleClick(this, keys, point);
}

void Control::onMouseWheel(DWORD value, POINT point)
{
    if (mOnMouseWheel) mOnMouseWheel(this, value, point);
}

LRESULT Control::procedure(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(this->mHwnd, uMsg, wParam, lParam);
}

inline DWORD Control::Style::get()
{
    return GetWindowLong(mOuter->mHwnd, GWL_STYLE);
}

inline bool Control::Style::has(DWORD f)
{
    return get() & f;
}

inline void Control::Style::add(DWORD f)
{
    SetWindowLongPtr(mOuter->mHwnd, GWL_STYLE, get() | f);
}

inline void Control::Style::subs(DWORD f)
{
    SetWindowLongPtr(mOuter->mHwnd, GWL_STYLE, get() & ~f);
}