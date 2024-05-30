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

	g_ctx.m_send_packet = reinterpret_cast<bool*>(*reinterpret_cast<byte**>(_ebp) - 0x1);

	g_movement.handle(cmd);

	/*
	v3 = a1;
	v4 = a2;
	if (!dword_1088766)
		return 0;
	sub_1007D56();
	sub_10080A80();
	if (a3)
		*/
	return false;
}

void __declspec(naked) __stdcall hook_createmove(int sequence_number, float input_sample_frametime, bool active) noexcept
{
	__asm
	{
		LEA  EAX, [EBP - 01]
		PUSH EAX
		PUSH[ESP + 0x10]
		PUSH[ESP + 0x10]
		PUSH[ESP + 0x10]
		CALL create_move_h
		RET 0x0C
	}
}

void hooks::init()
{
	MH_CreateHook(REINTERPRET_P(get_virtual(g_css.d3d_device, 17)), present_h, REINTERPRET_PP(&present_original));
	MH_CreateHook(REINTERPRET_P(get_virtual(g_css.m_client_mode, 21)), hook_createmove, REINTERPRET_PP(&create_move_original));
}

void hooks::unhook()
{

	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);

}
