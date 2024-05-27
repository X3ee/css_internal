#include "sdk.h"
#include "hooks.h"
#include "visuals.h"
#include "render.h"
#include "movement.h"
#include "localplayer.h"
#include <mutex>
#include "minhook.h"
hooks g_hooks;
using present_fn = long(__stdcall*)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
present_fn  
present_original = {};
std::once_flag                                     m_flg = {};

cvmt_hook* enginevgui_table = nullptr;
using create_move_fn = bool(__stdcall*)(float, CUserCmd*);
create_move_fn                                     create_move_original = {};

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

bool __stdcall create_move_h(float input_sample_frametime, CUserCmd* cmd)
{
	if (!cmd || !cmd->commandNumber)
		return create_move_original(input_sample_frametime, cmd);

	DWORD _ebp;
	__asm mov _ebp, ebp;

	localplayer.m_send_packet = reinterpret_cast<bool*>(*reinterpret_cast<byte**>(_ebp) - 0x1);

	g_movement.handle(cmd);




	return false;
}

void hooks::init()
{
	MH_CreateHook(REINTERPRET_P(get_virtual(g_css.d3d_device, 17)), present_h, REINTERPRET_PP(&present_original));
	MH_CreateHook(REINTERPRET_P(get_virtual(g_css.m_client_mode, 21)), create_move_h, REINTERPRET_PP(&create_move_original));
}

void hooks::unhook()
{



}
