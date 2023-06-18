#pragma once
#include <memory>
#include "../JNI/JNI.h"
#include "../Dependencies/MinHook/MinHook.h"

class Hooks
{
public:
    Hooks() {
        MH_Initialize();
        isInit = true;
        
    }
    ~Hooks() {
        isInit = false;
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, oriWndProc);
    }
    bool GetInit() {
        return isInit;

    }

    // This function will be called each time WndProc is called.
    static LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) // Each keystroke will PostMessage with uMsg down and wParam the key.
        {
        case WM_LBUTTONDOWN:
            KeyListener[VK_LBUTTON] = true;
            break;
        case WM_LBUTTONUP:
            KeyListener[VK_LBUTTON] = false;
            break;
        case WM_RBUTTONDOWN:
            KeyListener[VK_RBUTTON] = true;
            break;
        case WM_RBUTTONUP:
            KeyListener[VK_RBUTTON] = false;
            break;
        case WM_MBUTTONDOWN:
            KeyListener[VK_MBUTTON] = true;
            break;
        case WM_MBUTTONUP:
            KeyListener[VK_MBUTTON] = false;
            break;
        case WM_XBUTTONDOWN:
        {
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
            {
                KeyListener[VK_XBUTTON1] = true;
            }
            else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
            {
                KeyListener[VK_XBUTTON2] = true;
            }
            break;
        }
        case WM_XBUTTONUP:
        {
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
            {
                KeyListener[VK_XBUTTON1] = false;
            }
            else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
            {
                KeyListener[VK_XBUTTON2] = false;
            }
            break;
        }
        case WM_KEYDOWN:
            KeyListener[wParam] = true;
            break;
        case WM_KEYUP:
            KeyListener[wParam] = false;
            break;
        default:
            break;
        }

        return CallWindowProcW((WNDPROC)oriWndProc, hWnd, uMsg, wParam, lParam); // Call the original Function
    }

    static LONG_PTR oriWndProc; // Original WndProc
    static bool KeyListener[256]; // Key Listener
    static HWND hWnd; // Window Handle

private:
    bool isInit = false;
};

inline std::unique_ptr<Hooks> hooks;

