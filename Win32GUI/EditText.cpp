#include "EditText.h"

EditText::EditText(Control* parent, TSTRING text, int width, int height)
    :EditText(parent, text, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        { 0, 0, width, height })
{}

EditText::EditText(Control* parent, TSTRING text, DWORD style, RECT rect)
    : Control(parent, WC_EDIT, text.c_str(), style, rect)
{}

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

LRESULT EditText::onDraw(HDC hdc)
{
    // Do not change background by default.
    // It is ugly. Rewrite if you REALLY want to.
    SetTextColor(hdc, mFColor);
    return (INT_PTR)GetStockObject(WHITE_BRUSH);
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
