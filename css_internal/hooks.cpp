#include "sdk.h"
#include "hooks.h"
#include "visuals.h"
#include "render.h"
#include <mutex>
#include "minhook.h"
hooks g_hooks;
using present_fn = long(__stdcall*)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
present_fn  
present_original = {};
std::once_flag                                     m_flg = {};
cvmt_hook* enginevgui_table = nullptr;
long __stdcall present_h(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region)
{
	std::call_once(m_flg, [&] {
		g_render.initialize(device);
	
		});

	g_render.startrenderstate(device);

	g_visuals.paint();

	g_render.endrenderstate(device);

	return present_original(device, source_rect, dest_rect, dest_window_override, dirty_region);
}

void hooks::init()
{
	MH_CreateHook(REINTERPRET_P(get_virtual(g_css.d3d_device, 17)), present_h, REINTERPRET_PP(&present_original));
	
}

void hooks::unhook()
{



}
