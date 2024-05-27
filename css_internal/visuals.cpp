#include "visuals.h"
#include "framework.h"
#include "sdk.h"
#include "css.h"
visuals g_visuals;
// esp  func
int d(CCSPlayer* player)
{


}

void visuals::run_esp()
{
	auto local = reinterpret_cast<CCSPlayer*>(g_css.m_entitylist->GetClientEntity(g_css.m_engine->GetLocalPlayer()));
	if (!local)
		return;

	for (auto i = 0; i < g_css.m_entitylist->GetHighestEntityIndex(); i++)
	{
		auto entity = reinterpret_cast<CCSPlayer*>(g_css.m_entitylist->GetClientEntity(i));
		if (!entity || entity->IsDormant())
			continue;

		auto client_class = entity->GetClientClass();
		if (!client_class)
			continue;

		if (client_class->m_ClassID == C_CSPlayer)
			d(entity);
	}
}

