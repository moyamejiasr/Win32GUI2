#include "../Win32GUI/Window.h"
#include "../Win32GUI/TextView.h"
#include "../Win32GUI/MultiEditText.h"
#include "../Win32GUI/Button.h"

int main() {
	Window main(L"Hello world");
	main.show();

	TextView txt(&main, L"Hello world, how are you feeling today?", 92, 68);
	txt.staticEdge(true);
	txt.position(12, 6);

	EditText edit(&main, L"", 120);
	edit.position(12, 80);
	edit.password(true);

	MultiEditText medit(&main, L"Write here", 120);
	medit.heightInLines(3);
	medit.position(116, 6);
	medit.hScrollbar(true);
	medit.vScrollbar(true);

	Button btn(&main, L"OK");
	btn.position(116, 138);
	btn.enhanced(true);
	btn.flat(true);

	Control::join();
	return 0;
}