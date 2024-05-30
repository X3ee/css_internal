#include "visuals.h"
#include "framework.h"
#include "sdk.h"
#include "css.h"
#include "render.h"
#include "localplayer.h"
visuals g_visuals;

void visuals::paint()
{

	this->watermark();


	if (!g_ctx.local())
		return;

	if (!g_css.m_engine->IsInGame())
		return;
}

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

void visuals::watermark()
{
	float color_[4] = { 255.f, 255.f, 255.f, 255.f };
	vec3_t x_, y_;
	g_render.text("css internal", 5, 5, g_fonts.d3d_font,
		g_render.textcolor(color_), true, false);

}

