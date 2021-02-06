#include "../Win32GUI/Window.h"
#include "../Win32GUI/TextView.h"
#include "../Win32GUI/MultiEditText.h"
#include "../Win32GUI/ImageButton.h"
#include "../Win32GUI/CommandLink.h"

int main() {
	Window main(L"Hello world");
	main.show();

	TextView txt(&main, L"Hello world, how are you feeling today?", 92, 68);
	txt.staticEdge(true);
	txt.position(12, 6);

	EditText edit(&main, L"Example", 120);
	edit.position(12, 80);
	edit.textAlign(Right);

	CommandLink cml(&main, L"Command", 120, 58);
	cml.position(138, 80);
	cml.note(L"Test");

	MultiEditText medit(&main, L"Write here", 120);
	medit.heightInLines(3);
	medit.position(116, 6);
	medit.hScrollbar(true);
	medit.vScrollbar(true);

	Button btn(&main, L"OK");
	btn.position(12, 138);
	btn.enhanced(true);
	btn.flat(true);
	btn.icon(LoadIcon(NULL, IDI_HAND));

	ImageButton ibtn(&main, L"OK");
	ibtn.position(93, 138);
	ibtn.icon(LoadIcon(NULL, IDI_HAND));

	Control::join();
	return 0;
}