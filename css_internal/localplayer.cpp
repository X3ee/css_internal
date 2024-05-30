#include "localplayer.h"

ctx LocalPlayer;

CCSPlayer* ctx::local()
{
	return reinterpret_cast<CCSPlayer*>(g_css.m_entitylist->GetClientEntity(g_css.m_engine->GetLocalPlayer()));
}
