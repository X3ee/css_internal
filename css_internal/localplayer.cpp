#include "localplayer.h"

local localplayer;

CCSPlayer* local::getlocalplayer()
{
	return reinterpret_cast<CCSPlayer*>(g_css.m_entitylist->GetClientEntity(g_css.m_engine->GetLocalPlayer()));
}
