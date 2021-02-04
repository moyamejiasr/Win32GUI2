#include "../Win32GUI/Window.h"
#include "../Win32GUI/TextView.h"

int main() {
	Window main(L"Hello world");
	TextView txt(&main, L"Hello world, how are you feeling today?");
	main.show();

	Control::join();
	return 0;
}