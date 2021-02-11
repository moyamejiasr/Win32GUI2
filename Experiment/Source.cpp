
#include "../Win32GUI/Manager.h"

int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Window window(L"Test-Window");
	window.textSize(12);

	GroupBox box(&window, L"Test", {12, 12, 280, 162});

	TextView text(&box, L"Some TEXT", box.clientRect());
	text.border(true);

	window.show();
	return Control::join();
}