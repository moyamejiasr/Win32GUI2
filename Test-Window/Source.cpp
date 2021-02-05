#include "../Win32GUI/Window.h"
#include "../Win32GUI/TextView.h"
#include "../Win32GUI/MultiEditText.h"

int main() {
	Window main(L"Hello world");
	main.show();

	TextView txt(&main, L"Hello world, how are you feeling today?", 92, 68);
	txt.staticEdge(true);
	txt.position(12, 6);

	EditText edit(&main, L"", 120);
	edit.position(116, 6);
	edit.password(true);

	MultiEditText medit(&main, L"Write here", 120);
	medit.heightInLines(3);
	medit.position(116, 54);
	medit.hScrollbar(true);
	medit.vScrollbar(true);

	Control::join();
	return 0;
}