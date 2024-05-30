#include "css.h"
#include "hooks.h"
#include "interfaces.h"
int cheat(HMODULE hModule) {
    g_interfaces.init();
    css::initialize();
    g_hooks.init();

    while (css::update()) {
        if (GetAsyncKeyState(0x78) & 1)
            break;
        Sleep(100);
    }

    css::destroy();


    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)cheat, hModule, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

