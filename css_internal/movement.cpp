#include "movement.h"

void movement::handle(CUserCmd* cmd)
{
	if (!g_css.m_engine->IsConnected() && !g_css.m_engine->IsInGame())
		return;

}

void movement::faststop(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<CCSPlayer*>(g_css.m_entitylist->GetClientEntity(g_css.m_engine->GetLocalPlayer()));
	if (local_player->GetMoveType()  != MOVETYPE_WALK)
		return;



}

void movement::bhop(CUserCmd* cmd)
{

}
