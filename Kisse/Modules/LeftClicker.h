#pragma once
#include <Windows.h>
#include <random>

void clickerthread();

inline HHOOK hookdoMouse;
inline bool pressedclicker;
inline bool mouseDown;
inline bool othermouse;

enum ClickerMode {
    BLATANT,
    JITTER,
    BUTTER
};


namespace clicker {
    extern float rightClickerCPS;
}

extern ClickerMode currentMode;
extern ClickerMode currentMode = JITTER;
enum class MouseClick : int
{
    Left, Right
};

namespace hook
{
    inline LRESULT __stdcall mouse_callback(int code, WPARAM wparam, LPARAM lparam)
    {
        MSLLHOOKSTRUCT* hook = (MSLLHOOKSTRUCT*)lparam;

        if ((hook->flags == LLMHF_INJECTED) || (hook->flags == LLMHF_LOWER_IL_INJECTED))
            return false;

        if ((hook->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
            return false;

        if (wparam != WM_MOUSEMOVE)
        {
            if ((hook->flags == LLMHF_INJECTED) || (hook->flags == LLMHF_LOWER_IL_INJECTED))
                return false;

            switch (wparam)
            {
            case WM_LBUTTONDOWN:
                mouseDown = true;
                break;
            case WM_LBUTTONUP:
                mouseDown = false;
                break;
            case WM_RBUTTONDOWN:
                othermouse = true;
                break;
            case WM_RBUTTONUP:
                othermouse = false;
                break;
            }
        }
        return CallNextHookEx(hookdoMouse, code, wparam, lparam);
    }

    inline DWORD WINAPI hookmouse()
    {
        hookdoMouse = SetWindowsHookEx(WH_MOUSE_LL, &mouse_callback, NULL, 0);
        MSG msg;

        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        UnhookWindowsHookEx(hookdoMouse);
        return 0;
    }
}

namespace Random
{
   
    inline std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    __forceinline int GenerateNum(int min, int max)
    {
      
        std::uniform_int_distribution die{ min, max };

       
        return die(Random::mersenne);
    }
}


namespace clicker {
    inline bool C_toggle;
    inline bool C_InMC;
    inline int CPS = 1;
}
