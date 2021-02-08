#include "MultiEditText.h"

MultiEditText::MultiEditText(Control* parent, TSTRING text, int width, int height)
    :MultiEditText(parent, text, { 0, 0, width, height })
{}

MultiEditText::MultiEditText(Control* parent, TSTRING text, RECT rect)
    : MultiEditText(parent, text, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
        | ES_AUTOVSCROLL | ES_MULTILINE, rect)
{}

MultiEditText::MultiEditText(Control* parent, TSTRING text, DWORD style, RECT rect)
    : EditText(parent, text, style, rect)
{}

void MultiEditText::heightInLines(LONG count)
{
    SIZE cur = size();
    cur.cy = 23 + 16 * (count);
    size(cur);
}
