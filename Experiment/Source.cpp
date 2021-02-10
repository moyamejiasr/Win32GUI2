
#include "../Win32GUI/Manager.h"

int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Window window(L"Test-Window");
	// TODO when only right apply jump-line
	RECT r{0, 0, CW_USEDEFAULT, CW_USEDEFAULT};
	TextView text(&window, L"Hello world", r);
	RECT ri{ 7, 7, 50, 14 };
	text.pointRect(ri);
	window.show();
	return Control::join();
}