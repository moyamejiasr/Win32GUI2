#include "EditText.h"

EditText::EditText(Control* parent, const TSTRING& text, int width, int height)
    :EditText(parent, text, { 0, 0, width, height })
{}

EditText::EditText(Control* parent, const TSTRING& text, RECT&& rect)
    : EditText(parent, text, rect)
{}

EditText::EditText(Control* parent, const TSTRING& text, RECT& rect)
    : EditText(parent, text, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        &rect)
{}

EditText::EditText(Control* parent, const TSTRING& text, DWORD style, PRECT rect)
    : Control(parent, WC_EDIT, text.c_str(), style, rect)
{
    // This hack allows us to preserve the white background
    // unless it is specifically requested otherwise.
    // Window-color backgrounds are ugly.
    mBColor = 0xFFFFFF;
}

Align EditText::textAlign()
{
    DWORD s = style.get();
    if (s & ES_CENTER) return Center;
    if (s & ES_RIGHT) return Right;
    return Left;
}

bool EditText::lowercase()
{
    return style.has(ES_LOWERCASE);
}

bool EditText::number()
{
    return style.has(ES_NUMBER);
}

bool EditText::uppercase()
{
    return style.has(ES_UPPERCASE);
}

void EditText::textAlign(Align type)
{
    // Remove both, center(1) and right(2)
    style.subs(3);
    switch (type)
    {
    case Center:
        style.add(ES_CENTER);
        break;
    case Right:
        style.add(ES_RIGHT);
        break;
    }
}

void EditText::lowercase(bool state)
{
    if (state) style.add(ES_LOWERCASE);
    else style.subs(ES_LOWERCASE);
}

void EditText::number(bool state)
{
    if (state) style.add(ES_NUMBER);
    else style.subs(ES_NUMBER);
}

void EditText::uppercase(bool state)
{
    if (state) style.add(ES_UPPERCASE);
    else style.subs(ES_UPPERCASE);
}

bool EditText::keepSelection()
{
    return style.has(ES_NOHIDESEL);
}

bool EditText::password()
{
    return style.has(ES_PASSWORD);
}

bool EditText::readonly()
{
    return style.has(ES_READONLY);
}

void EditText::keepSelection(bool state)
{
    if (state) style.add(ES_NOHIDESEL);
    else style.subs(ES_NOHIDESEL);
}

void EditText::password(bool state)
{
    // ES_PASSWORD needs special message
    // when control is already created.
    SendMessage(mHwnd, EM_SETPASSWORDCHAR, state ? '*' : FALSE, NULL);
}

void EditText::readonly(bool state)
{
    // ES_READONLY needs special message
    // when control is already created.
    SendMessage(mHwnd, EM_SETREADONLY, state, NULL);
}

LRESULT EditText::procedure(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (HIWORD(wParam))
    {
    case EN_CHANGE:
        break;
    case EN_MAXTEXT:
        break;
    }
    return DefWindowProc(mHwnd, uMsg, wParam, lParam);
}

MultiEditText::MultiEditText(Control* parent, const TSTRING& text, int width, int height)
    :MultiEditText(parent, text, { 0, 0, width, height })
{}

MultiEditText::MultiEditText(Control* parent, const TSTRING& text, RECT&& rect)
    : MultiEditText(parent, text, rect)
{}

MultiEditText::MultiEditText(Control* parent, const TSTRING& text, RECT& rect)
    : MultiEditText(parent, text, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
        | ES_AUTOVSCROLL | ES_MULTILINE, &rect)
{}

MultiEditText::MultiEditText(Control* parent, const TSTRING& text, DWORD style, PRECT rect)
    : EditText(parent, text, style, rect)
{}

void MultiEditText::heightInLines(LONG count)
{
    SIZE cur = size();
    cur.cy = 23 + 16 * (count);
    size(cur);
}
