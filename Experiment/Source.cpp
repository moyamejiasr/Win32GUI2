
#include "../Win32GUI/Manager.h"

int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	RECT rWindow{ CW_USEDEFAULT, CW_USEDEFAULT, 800, 600 };
	Window window(L"Test-Window", rWindow);

	RECT t1Rect{ -7, -7, CW_USEDEFAULT, CW_USEDEFAULT };
	TextView text(&window, L"Some", t1Rect);
	text.backColor(RGB(125, 255, 255));

	window.show();
	return Control::join();
}