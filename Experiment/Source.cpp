
#include "../Win32GUI/Manager.h"

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	Window window(L"Test-Window");
	RECT r{ -7, -7, CW_USEDEFAULT, CW_USEDEFAULT };
	TextView text(&window, L"Some", r);
	text.backColor(RGB(125, 255, 255));
	std::cout << r.left << " " << r.top << " " << r.right << " " << r.bottom << std::endl;
	//text.border(true);

	window.show();
	return Control::join();
}