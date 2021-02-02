#pragma once
#pragma warning (disable : 26495)

#include <iostream>
#include <string>
#include <windows.h>

#ifdef UNICODE
typedef std::wstring TSTRING;
#define _IOTA(X) std::to_wstring(X)
#else /* Multi-Byte */
typedef std::string TSTRING;
#define _IOTA(X) std::to_string(X)
#endif

class WndClass : protected WNDCLASSEX
{
public:
	WndClass(WNDPROC, TSTRING, UINT = CS_DBLCLKS);
	WndClass(HINSTANCE, WNDPROC, TSTRING, UINT);
	bool success();
	PCTSTR name();
	HINSTANCE instance();
	static WndClass& get(TSTRING);
	static WndClass& get(HINSTANCE, TSTRING);

private:
	WndClass();
	WndClass(const WndClass&) = delete;
	bool mSuccess;
	TSTRING mName;
};

