#include "css.h"
#include "framework.h"
#include "console.h"
#include "localplayer.h"
#include "hooks.h"
css g_css;

DWORD_PTR get_module_base_address(const char* name)
{
    HMODULE m = GetModuleHandleA(name);

    if (m == 0)
        return 0;

    MODULEINFO module_info;
    GetModuleInformation(GetCurrentProcess(), m, &module_info, sizeof(module_info));

    return (DWORD_PTR)module_info.lpBaseOfDll;
}

void css::initialize() {
  init_interfaces(); // Get interface pointers and game stuff..
  g_con.main("cash hack");
  g_con.log("base adress 0x%p\n"), (void*)get_module_base_address("hl2.exe");
  g_con.log("\ninterfaces no bitches\n");
  g_css.m_cvar->ConsoleColorPrintf(white, "css");
}

void css::destroy() {
    g_con.log("unhooked\n\n");
    g_hooks.unhook();
    g_con.undo();
}

void css::init_interfaces() {
  auto engine_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"));
  auto client_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface")); 
  auto vstdlib_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface"));
  auto vphysics_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface"));
  auto vguimatsurface_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface"));
  auto panel = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface"));
 
  m_client = reinterpret_cast<IBaseClientDll*>(client_factory("VClient017", nullptr)); // also FF D0 83 C4 08 A3 ? ? ? ? C6 (engine.dll) 0xA3949 from engine.dll
  m_panel = reinterpret_cast<IPanel*>(client_factory("VGUI_Panel009", nullptr));
  m_surface = reinterpret_cast<ISurface*>(vguimatsurface_factory("VGUI_Surface030", nullptr));
  m_cvar = reinterpret_cast<ICvar*>(vstdlib_factory("VEngineCvar004", nullptr));
  m_engine = reinterpret_cast<IVEngineClient*>(engine_factory("VEngineClient014", nullptr));
  m_entitylist = reinterpret_cast<IClientEntityList*>(client_factory("VClientEntityList003", nullptr));

  static auto client_mode_fn = *(uintptr_t*)(
      util::find_pattern("client.dll", "89 04 B5 ? ? ? ? E8") + 3);

  m_client_mode = **(ClientMode***)(client_mode_fn);

  static auto devicefn = *(uintptr_t*)(
      util::find_pattern("shaderapidx9.dll", "A1 ? ? ? ? 8D 53 08") + 1);

  m_input = **reinterpret_cast<CInput***>(
      util::find_pattern("client.dll", "8B 0D ? ? ? ? 8B 01 FF 60 44") + 2);

  d3d_device = **reinterpret_cast<IDirect3DDevice9***>(devicefn);

}


bool css::update() {
    return true;
}
