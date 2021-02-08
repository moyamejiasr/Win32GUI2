#include "CommandLink.h"

CommandLink::CommandLink(Control* parent, TSTRING text, int width, int height)
	:CommandLink(parent, text, { 0, 0, width, height })
{}

CommandLink::CommandLink(Control* parent, TSTRING text, RECT rect)
	: CommandLink(parent, text, WS_CHILD | WS_VISIBLE | BS_COMMANDLINK, rect)
{}

CommandLink::CommandLink(Control* parent, TSTRING text, DWORD style, RECT rect)
	: Button(parent, text, style, rect)
{}

TSTRING CommandLink::note()
{
	int len = (int)Button_GetNoteLength(mHwnd) + 1;
	TCHAR* buff = new TCHAR[len];
	Button_GetNote(mHwnd, buff, len);
	TSTRING result = buff; delete[] buff;
	return result;
}

void CommandLink::note(TSTRING text)
{
	Button_SetNote(mHwnd, text.c_str());
}
