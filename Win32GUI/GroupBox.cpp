#include "GroupBox.h"

GroupBox::GroupBox(Control* parent, TSTRING text, int width, int height)
    :GroupBox(parent, text, { 0, 0, width, height })
{}

GroupBox::GroupBox(Control* parent, TSTRING text, RECT rect)
    : GroupBox(parent, text, WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_NOTIFY, rect)
{}

GroupBox::GroupBox(Control* parent, TSTRING text, DWORD style, RECT rect)
    : Control(parent, WC_BUTTON, text.c_str(), style, rect)
{
    // Hacky-hack to make GroupBoxes actually notify
    // parents of children actions.
    SetWindowSubclass(mHwnd, &GroupSubClass, 1, 0);
}

LRESULT GroupBox::GroupSubClass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        SendMessage(GetParent(hWnd), uMsg, wParam, lParam);
        break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}