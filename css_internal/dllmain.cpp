﻿#include "css.h"
#include "hooks.h"

int css(HMODULE hModule) {

    g_css.initialize();
    g_hooks.init();

    while (g_css.update()) {
        if (GetAsyncKeyState(VK_F9) & 1)
            break;
        Sleep(100);
    }

    g_css.dispose();


    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)css, hModule, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

