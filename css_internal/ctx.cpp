#include "ctx.h"
ctx g_ctx;

CCSPlayer* ctx::local()
{
	return reinterpret_cast<CCSPlayer*>(g_interfaces.m_entitylist->GetClientEntity(g_interfaces.m_engine->GetLocalPlayer()));
}
