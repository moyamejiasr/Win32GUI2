#pragma once
#include "Window.h"
#ifndef _MINIMAL
#include "TextView.h"
#include "EditText.h"
#include "MultiEditText.h"
#include "Button.h"
#include "ImageButton.h"
#include "CommandLink.h"
#endif

#define Invisible (HBRUSH)GetStockObject(HOLLOW_BRUSH)
#define Dialog(m, t) MessageBox(NULL, m, t, MB_ICONINFORMATION | MB_OK)