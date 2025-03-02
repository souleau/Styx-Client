#include <Windows.h>
#include <iostream>
#include "Kisse/Kisse.h"
//#include "Login/Login.hpp"


#define KISSE_INJECTOR 66666


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    return 0;
}


BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case KISSE_INJECTOR:
    case DLL_PROCESS_ATTACH:
    {


 

        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        if (!Kisse::init(hinstDLL))
        {
            std::cin.ignore();
           // FreeConsole();
            return FALSE;
        }
        HWND hWnd = GetConsoleWindow();
        ShowWindow(hWnd, SW_HIDE);
        std::cout << "Init success" << std::endl;
        return TRUE;
    }

    case DLL_THREAD_ATTACH:

        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
      
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {

      
            //process termination
            Kisse::partialClean();
            break;
        }
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}



int main() {


    std::cout << "success\n";
    return 0;
}