#include "Hooks.h"
bool	Hooks::KeyListener[256] = {};
HWND	Hooks::hWnd = FindWindowA(NULL, "Badlion Minecraft Client v3.16.1-681a1c5-PRODUCTION3 (1.8.9)");
	
LONG_PTR	Hooks::oriWndProc = SetWindowLongPtrW(hooks->hWnd, GWLP_WNDPROC, (LONG_PTR)Hooks::WndProc);