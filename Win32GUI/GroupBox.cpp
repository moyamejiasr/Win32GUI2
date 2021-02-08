#include "GroupBox.h"

GroupBox::GroupBox(Control* parent, TSTRING text, int width, int height)
    :GroupBox(parent, text, { 0, 0, width, height })
{}

GroupBox::GroupBox(Control* parent, TSTRING text, RECT rect)
    : GroupBox(parent, text, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, rect)
{}

GroupBox::GroupBox(Control* parent, TSTRING text, DWORD style, RECT rect)
    : Control(parent, WC_BUTTON, text.c_str(), style, rect)
{}