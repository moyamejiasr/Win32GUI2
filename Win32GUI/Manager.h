#pragma once
#include "Window.h"
#include "TextView.h"
#include "EditText.h"
#include "MultiEditText.h"
#include "Button.h"
#include "GroupBox.h"
#include "ImageButton.h"
#include "CommandLink.h"

#define Invisible (HBRUSH)GetStockObject(HOLLOW_BRUSH)
#define Dialog(m, t) MessageBox(NULL, m, t, MB_ICONINFORMATION | MB_OK)