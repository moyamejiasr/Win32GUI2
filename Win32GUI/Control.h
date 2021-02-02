#pragma once
#pragma warning (disable : 26495)

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windowsx.h>
#include <functional>
#include <vector>
#include "WndClass.h"

#define LPARAM2POINT(pm) { GET_X_LPARAM(pm), GET_Y_LPARAM(pm) }
#define AsControl(hwnd) (Control*)GetWindowLongPtr(hwnd, GWLP_USERDATA)
#define SetControl(hwnd, ptr) SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ptr)

// Common callback definitions
class Control;
class Window;
typedef std::function<bool(Control*)> OnIterFunc;
typedef std::function<LRESULT(Control*, HDC)> OnDrawFunc;
typedef std::function<LRESULT(Control*, bool)> OnHoverFunc;
typedef std::function<void(Control*, DWORD, POINT)> OnClickFunc;
typedef std::function<void(Control*, DWORD, POINT)> OnDoubleClickFunc;
typedef std::function<void(Control*, DWORD, POINT)> OnMouseWheelFunc;

/*	Abstract class. It must not be implemented but inherited or 
	casted to/from. It handles most of the common Win32 Windows 
	functions. 
	IMPORTANT do not attempt to invoke the copy constructor. It 
	has been deleted in order to prevent destructor calls since 
	those will destroy the object.
	@constructor none
*/
class Control
{
public:
	////////////////////////////////////////////////////////////
	// Window: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	Returns the control DC.
		@return HDC
	*/
	HDC hdc();
	/*	Returns the control HWND.
		@return HWND
	*/
	HWND hwnd();
	/*	Returns the control associated HINSTANCE.
		@return HINSTANCE
	*/
	HINSTANCE hinstance();
	/*	Returns the parent control if any.
		@return Control*
	*/
	Control* parent();
	/*	Returns the parsed control Text/Title field.
		@return TSTRING text
	*/
	TSTRING text();
	/*	Returns a Style interface that can be accessed to change 
		any of its parameters.
		@return Style
	*/
	struct Style {
		/*	Returns the whole Style flags parameter.
			@return DWORD
		*/
		inline DWORD get();
		/*	Returns whether the Style has a specific flag.
			@param DWORD flag
			@return bool
		*/
		inline bool has(DWORD);
		/*	AdAppends a flag to the Style.
			@param DWORD flag
		*/
		inline void add(DWORD);
		/*	Removes a flag from the Style.
			@param DWORD flag
		*/
		inline void subs(DWORD);
		// Do not change these parameters. Style may not work.
		Control* mOuter; DWORD mType;
	} style = { this, GWL_STYLE }, exstyle = { this, GWL_EXSTYLE };

	/*	Sets the parsed control Text/Title field.
		@param TSTRING text
	*/
	void text(TSTRING);

	////////////////////////////////////////////////////////////
	// Rectangle: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	Returns the size of the Control with a struct.
		@return SIZE (cx, cy)
	*/
	SIZE size();
	/*	Returns the position of the Control with a struct.
		@return POINT (x, y)
	*/
	POINT position();
	/*	Returns the rectangle of the Control in a struct.
		@return RECT (left, top, right, bottom)
	*/
	RECT rect();
	/*	Returns the client rectangle of the Control in a struct. 
		It differs from the rect function in that it calculates 
		the portion of the rectangle where the child components 
		will be placed at.
		@return RECT (left, top, right, bottom)
	*/
	RECT clientRect();

	/*	Sets the size of the Control with two LONG params.
		@param LONG width
		@param LONG height
	*/
	void size(LONG, LONG);
	/*	Sets the size of the Control with a struct.
		@param SIZE (cx, cy)
	*/
	void size(SIZE);
	/*	Sets the position of the Control with two LONG params.
		@param LONG x
		@param LONG y
	*/
	void position(LONG, LONG);
	/*	Sets the position of the Control with a struct.
		@param POINT (x, y)
	*/
	void position(POINT);
	/*	Sets the rectangle of the Control in a struct.
		@param RECT (left, top, right, bottom)
	*/
	void rect(RECT);
	/*	Sets the rectangle of the Control in a struct. 
		It differs from the rect function in that it calculates 
		the size of the normal rectangle needed to allocate a 
		client rectangle of the given size.
		@param RECT (left, top, right, bottom)
	*/
	void clientRect(RECT);

	////////////////////////////////////////////////////////////
	// Appearance: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	No common appearance */

	////////////////////////////////////////////////////////////
	// Behavior: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	Returns true if the control is enabled or false if not.
		@return bool
	*/
	bool enabled();
	/*	Returns true if the control is visible or false if not.
		@return bool
	*/
	bool visible();

	/*	Sets the enabled state with a boolean value.
		@param bool state
	*/
	void enabled(bool);
	/*	Sets the visible state with a boolean value.
		@param bool state
	*/
	void visible(bool);

	////////////////////////////////////////////////////////////
	// Font: Getters & Setters
	////////////////////////////////////////////////////////////

	/*	Returns the color currently used for the background. 
		IMPORTANT not every Control uses this parameter.
		@return COLORREF DWORD(RGB)
	*/
	COLORREF backColor();
	/*	Returns the color currently used for the foreground. 
		IMPORTANT not every Control uses this parameter.
		@return COLORREF DWORD(RGB)
	*/
	COLORREF textColor();
	/*	Returns the font currently used in the control text. 
		IMPORTANT not every Control uses this parameter.
		@return TSTRING length(32-1)
	*/
	TSTRING textFont();
	/*	Returns the size currently used in the control text. 
		IMPORTANT not every Control uses this parameter.
		@return LONG
	*/
	LONG textSize();
	/*	Returns whether the text is italic or not. 
		IMPORTANT not every Control uses this parameter.
		@return bool
	*/
	bool textItalic();
	/*	Returns whether the text is underline or not. 
		IMPORTANT not every Control uses this parameter.
		@return bool
	*/
	bool textUnderline();
	/*	Returns whether the text is strike-out or not. 
		IMPORTANT not every Control uses this parameter.
		@return bool
	*/
	bool textStrikeOut();

	/*	Sets the color currently used for the background. 
		IMPORTANT not every Control uses this parameter.
		@param COLORREF DWORD(RGB) color
	*/
	void backColor(COLORREF);
	/*	Sets the color currently used for the foreground. 
		IMPORTANT not every Control uses this parameter.
		@param COLORREF DWORD(RGB) color
	*/
	void textColor(COLORREF);
	/*	Sets the font currently used in the control text. 
		IMPORTANT not every Control uses this parameter.
		@param TSTRING MUST BE length(32-1) MAX
	*/
	void textFont(TSTRING);
	/*	Sets the size currently used in the control text. 
		IMPORTANT not every Control uses this parameter.
		@param LONG
	*/
	void textSize(LONG);
	/*	Sets whether the text is italic or not. 
		IMPORTANT not every Control uses this parameter.
		@param bool
	*/
	void textItalic(bool);
	/*	Sets whether the text is underline or not. 
		IMPORTANT not every Control uses this parameter.
		@param bool
	*/
	void textUnderline(bool);
	/*	Sets whether the text is strike-out or not. 
		IMPORTANT not every Control uses this parameter.
		@param bool
	*/
	void textStrikeOut(bool);

	////////////////////////////////////////////////////////////
	// Misc: Getters, Setters & Functions
	////////////////////////////////////////////////////////////

	/*	Returns whether the control is valid(exists) or has been 
		recycled/erased. 
		For this purpose it checks the HWND and makes a call to 
		the IsWindow function if needed.
		@return bool
	*/
	bool valid();
	/*	Returns the child count. It iterates through the first 
		child level counting each one. It is by no means an 
		efficient method but it is the only way to retrieve an 
		updated list. You can emulate it with forChildren call.
		@return UINT
	*/
	inline UINT childCount();

	/*	Sets the visible state of the window to true. This is 
		just an inline that calls the visible(true) function.
		@param none
	*/
	inline void show();
	/*	Sets the visible state of the window to false. This is 
		just an inline that calls the visible(false) function.
		@param none
	*/
	inline void hide();
	/*	Attempts to update/set the current font if any given a 
		previously setup LOGFONT.
		@param none
	*/
	void updateFont();
	/*	Attempts to redraw the whole Control(Window). 
		Useful when experiencing visual glitches.
		@param none
	*/
	void redraw();
	/*	Iterates through each children of the first level and 
		calls the OnIterFunc callback for each.
		@param OnIterFunc bool(Control*)
	*/
	void forChildren(OnIterFunc);
	/*	Sets the OnDrawFunc callback. 
		Only gets called when not overriding the caller method.
		@param OnDrawFunc LRESULT(Control*, HDC)
	*/
	void setOnDraw(OnDrawFunc);
	/*	Sets the OnHoverFunc callback.
		Only gets called when not overriding the caller method.
		@param OnHoverFunc LRESULT(Control*, bool)
	*/
	void setOnHover(OnHoverFunc);
	/*	Sets the OnClickFunc callback. 
		Only gets called when not overriding the caller method.
		@param OnClickFunc void(Control*, DWORD, POINT)
	*/
	void setOnClick(OnClickFunc);
	/*	Sets the OnDoubleClickFunc callback. 
		Only gets called when not overriding the caller method.
		@param OnDoubleClickFunc void(Control*, DWORD, POINT)
	*/
	void setOnDoubleClick(OnDoubleClickFunc);
	/*	Sets the OnMouseWheelFunc callback. 
		Only gets called when not overriding the caller method.
		@param OnMouseWheelFunc void(Control*, DWORD, POINT)
	*/
	void setOnMouseWheel(OnMouseWheelFunc);
	/*	Attempts to destroy the window item and release 
		any allocated resources.
		@param none
	*/
	~Control();

protected:
	friend class Window;
	HWND mHwnd;
	COLORREF mBColor, mFColor;
	LOGFONT mFont;
	OnDrawFunc mOnDraw = NULL;
	OnHoverFunc mOnHover = NULL;
	OnClickFunc mOnClick = NULL;
	OnDoubleClickFunc mOnDoubleClick = NULL;
	OnMouseWheelFunc mOnMouseWheel = NULL;

	/*	Parent Constructor. Creates a parent window from the
		given arguments.
		@param HINSTANCE Current Instance NOT NULL
		@param PCTSTR WNDCLASS name
		@param PCTSTR Text
		@param DWORD Style
		@param RECT rectangle
	*/
	Control(HINSTANCE, PCTSTR, PCTSTR, DWORD, RECT);
	/*	Child Constructor. Creates a child window from the 
		given arguments.
		@param Control* Parent NOT NULL
		@param PCTSTR WNDCLASS name
		@param PCTSTR Text
		@param DWORD Style
		@param RECT rectangle
	*/
	Control(Control*, PCTSTR, PCTSTR, DWORD, RECT);
	/*	Destroyed copy constructor. We do this to prevent full 
		classes from being copied and then removed with a call 
		to the default destructor.
		@deprecated
	*/
	Control(const Control&) = delete;
	/*	Default onDraw function.
		Called by: Window::WndProc
	*/
	virtual LRESULT onDraw(HDC);
	/*	Default onHover function.
		Called by: Window::WndProc
	*/
	virtual void onHover(bool);
	/*	Default onClick function.
		Called by: Window::WndProc
	*/
	virtual void onClick(DWORD, POINT);
	/*	Default onDoubleClick function.
		Called by: Window::WndProc
	*/
	virtual void onDoubleClick(DWORD, POINT);
	/*	Default onMouseWheel function.
		Called by: Window::WndProc
	*/
	virtual void onMouseWheel(DWORD, POINT);
	/*	Default procedure for extra control messages.
		Called by: Window::WndProc
	*/
	virtual LRESULT procedure(UINT, WPARAM, LPARAM);
};