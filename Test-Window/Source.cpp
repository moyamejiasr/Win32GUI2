#include "../Win32GUI/Window.h"
#include "../Win32GUI/TextView.h"

int main() {
	Window main(L"Hello world");
	TextView txt(&main, L"Hello world, how are you feeling today?", 92, 68);
	txt.staticEdge(true);
	txt.position(12, 6);
	main.show();

	Control::join();
	return 0;
}