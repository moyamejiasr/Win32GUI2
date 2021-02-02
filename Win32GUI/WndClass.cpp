#include "WndClass.h"

WndClass::WndClass(WNDPROC procedure, TSTRING name, UINT uStyle)
	: WndClass(GetModuleHandle(NULL), procedure, name, uStyle)
{
}

WndClass::WndClass(HINSTANCE instance, WNDPROC procedure, TSTRING name, UINT uStyle)
{
	// Store copy for access later on
	mName = name;

	cbSize = sizeof(WNDCLASSEX);
	lpfnWndProc = procedure;
	hInstance = instance;
	lpszClassName = mName.c_str();
	style = uStyle;
	mSuccess = RegisterClassEx((LPWNDCLASSEX)this);
}

bool WndClass::success()
{
	return success;
}

PCTSTR WndClass::name()
{
	return lpszClassName;
}

HINSTANCE WndClass::instance()
{
	return hInstance;
}

WndClass& WndClass::get(TSTRING name)
{
	return get(GetModuleHandle(NULL), name);
}

WndClass& WndClass::get(HINSTANCE instance, TSTRING name)
{
	WndClass object;
	object.mSuccess = GetClassInfoEx(instance, name.c_str(), 
		(LPWNDCLASSEX)&object);
	return object;
}

WndClass::WndClass()
{
}
