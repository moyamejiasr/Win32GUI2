#include "../Win32GUI/Window.h"

int main() {
	Window main(L"Hello world");
	main.show();

	Control::join();
	return 0;
}