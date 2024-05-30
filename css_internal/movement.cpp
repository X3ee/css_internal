#include "movement.h"
#include "ctx.h"
movement g_movement;
void movement::handle(CUserCmd* cmd)
{
 if (!g_interfaces.m_engine->IsConnected() && !g_interfaces.m_engine->IsInGame())
 return;
 bhop();
	//jumpikiii();
}

/*
void movement::faststop(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<CCSPlayer*>(g_css.m_entitylist->GetClientEntity(g_css.m_engine->GetLocalPlayer()));
	if (local_player->GetMoveType()  != MOVETYPE_WALK)
		return;

}*/

void movement::bhop()
{
	/* need make gucci method */
	if (g_ctx.local()->GetMoveType() == MOVETYPE_LADDER ||
		g_ctx.local()->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (m_ucmd->buttons & IN_JUMP && !(g_ctx.local()->GetFlags() & FL_ONGROUND)) {
		m_ucmd->buttons &= ~IN_JUMP;
	}
}

/*void movement::jumpikiii()
{
	
	static auto sv_airaccelerate = g_css.m_cvar->FindVar(("sv_airaccelerate"));
	static bool was_onground = g_ctx.local()->GetFlags() & FL_ONGROUND;
	static vec3_t last_origin{ };
	static float ground_vel{ };
	static float last_jump_max_speed{ };
	static float last_height{ };
	static float last_dist{ };

	const float lj_threshold = sv_airaccelerate->GetFloat() < 15.f ? 190.f : 240.f;

	bool on_ground = localplayer.getlocalplayer()->GetFlags() & FL_ONGROUND;
	bool ducking = localplayer.getlocalplayer()->GetFlags() & FL_DUCKING;

	char jump_string[250] = { };

	if (on_ground) {
		int vertical = 0;

		if (!was_onground) {
			vec3_t cur_origin = localplayer.getlocalplayer()->GetOrigin();
			last_dist = cur_origin.dist_to(last_origin);

			if (std::abs(cur_origin.z - last_origin.z) >= (ducking ? 10.f : 5.f)) {
				vertical = cur_origin.z > last_origin.z ? 1 : -1;
			}

			if (ground_vel > 200.f && last_jump_max_speed > 260.f && std::abs(last_height) > 20.f) {
				if (vertical) {
					g_css.m_cvar->ConsoleDPrintf(jump_string, 250, ("[\3JUMP STAT\1] pre: %0.2f | max vel: %0.2f | height: %0.2f | duck: %d | \2%s\n"),
						ground_vel, last_jump_max_speed, last_height, ducking, vertical == 1 ? ("vertical") : ("dropjump"));
				}
				else {
					bool is_lj = last_dist > lj_threshold;
					g_css.m_cvar->ConsoleDPrintf(jump_string, 250, ("[\3JUMP STAT\1]: pre: %0.2f | max vel: %0.2f | height: %0.2f | duck: %d | dist: %c%0.2f\n"),
						ground_vel, last_jump_max_speed, last_height, ducking, is_lj ? 4 : 1, last_dist);
				}

				g_css.m_cvar->ConsoleDPrintf(0, 0, jump_string);
			}
		}
		last_origin = localplayer.getlocalplayer()->GetOrigin();
		last_jump_max_speed = 0.f;
		last_height = 0.f;
		ground_vel = localplayer.getlocalplayer()->m_vecVelocity().length2d();

		was_onground = true;
	}
	else {
		was_onground = false;
		float vel = localplayer.getlocalplayer()->m_vecVelocity().length2d();
		if (vel > last_jump_max_speed) {
			last_jump_max_speed = vel;
		}
		float delta = localplayer.getlocalplayer()->GetOrigin().z - last_origin.z;
		if (std::abs(delta) > std::abs(last_height)) {
			last_height = delta;
		}
	}
}*/
