#pragma once

#include <array>
#include <memory.h>

#include <Windows.h>

#include "framework.h"
#include <stdio.h>

#define dbgprint           printf_s
#define dbgvar(x)          printf_s("%16s -> %8x\n", #x, (uintptr_t) x)
#define dbginterface(x, y) printf_s("%32s -> %8x\n", x, (uintptr_t) x)

namespace util
{
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

    uintptr_t find_pattern(const char* szModule, const char* szSignature);
    std::uintptr_t get_rel32(std::uintptr_t address, std::uintptr_t offset, std::uintptr_t instruction_size);
    bool IsCodePtr(void* ptr);


}
struct vector {
    float x, y, z;
};






inline uintptr_t get_function_by_call(std::uintptr_t address, std::uintptr_t offset, std::uintptr_t instruction_size)
{
    return address + *reinterpret_cast<std::uintptr_t*>(address + offset) + instruction_size;
}

template <typename T>
inline T get_proc_address(uintptr_t mod, const char* s) {
    return (T)GetProcAddress((HMODULE)mod, s);
}
inline uintptr_t get_module_handle(const char* s) {
    uintptr_t module_ = (uintptr_t)GetModuleHandleA(s);
    if (!module_) {
        MessageBox(NULL, L"LoadInterfaces( ) failed! Check dll modules.", L"cheat::LoadInterfaces( )", NULL);
        return 0;
    }
    dbgprint("%32s => %8x\n", s, module_);
    return module_;
}

template <typename T1, typename T2>
inline T1 GetVFunction(T2* p, size_t index) {
    return (T1)((*(uintptr_t**)p)[index]);
}

template <typename F>
inline F GetInterfaceFromDll(uintptr_t dll, const char* interface_name) {
    typedef void* (__cdecl* GetInterface)(const char* s, int* a);
    GetInterface i = get_proc_address<GetInterface>(dll, "CreateInterface");
    return ((F)i(interface_name, nullptr));
}

typedef void* (*InstantiateInterfaceFn)();
struct InterfaceReg {
    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;
};

template <typename IT>
inline IT GetInterfacePtr(const char* name, InterfaceReg* interface_list) {

    for (InterfaceReg* current = interface_list; current; current = current->m_pNext)
    {
        if (!strcmp(name, current->m_pName)) {
            dbginterface(current->m_pName, current->m_CreateFn());
            return (IT)current->m_CreateFn();
        }
    }
    printf("! Interface \"%s\" not found :(\n", name);
}
