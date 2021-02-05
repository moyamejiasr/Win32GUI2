#include "MultiEditText.h"

MultiEditText::MultiEditText(Control* parent, TSTRING text, int width, int height)
    :MultiEditText(parent, text, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
        | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN, { 0, 0, width, height })
{}

MultiEditText::MultiEditText(Control* parent, TSTRING text, DWORD style, RECT rect)
    : EditText(parent, text.c_str(), style, rect)
{}