#pragma once

#include "util.h"
#include "netvars.h"
#include "css.h"
#include "vector.h"

namespace offsets {
    constexpr uintptr_t m_iHealth = 0x94;
    constexpr uintptr_t m_iTeamNum = 0x9C;
    constexpr uintptr_t m_fFlags = 0x350;
    constexpr uintptr_t m_vecAbsOrigin = 0x260;
    constexpr uintptr_t m_vecAbsAngles = 0x26C;
    constexpr uintptr_t m_vecViewOffset = 0xE8;
    static auto m_MoveType = *(uintptr_t*)(
        util::find_pattern("client.dll", "80 BE ? ? ? ? ? 75 2D") + 2);
} // namespace offsets



struct CBaseEntity {

    int GetHealth(void) {
        return *(int*)((uint8_t*)this + offsets::m_iHealth);
    }

    int GetMoveType(void) {
        return *(int*)((uint8_t*)this + offsets::m_MoveType);
    }

    int GetTeam(void) {
        return *(int*)((uint8_t*)this + offsets::m_iTeamNum);
    }

    NETVAR(m_vecVelocity, "CBaseEntity", "m_vecVelocity",  vec3_t);
    NETVAR(GetOrigin, "CBaseEntity", "m_vecOrigin", vec3_t);
   // m_vecOrigin
  

    float* GetAbsOrigin(void) {
        return (float*)((uint8_t*)this + offsets::m_vecAbsOrigin);
    }

    float* GetAbsAngles(void) {
        return (float*)((uint8_t*)this + offsets::m_vecAbsAngles);
    }

    float* GetViewOffset(void) {
        return (float*)((uint8_t*)this + offsets::m_vecViewOffset);
    }

    vec3_t GetEyePos()
    {
        vec3_t* orig = (vec3_t*)this->GetAbsOrigin();
        vec3_t* view = (vec3_t*)this->GetViewOffset();

        vec3_t eye = { orig->x + view->x,  orig->y + view->y,  orig->z + view->z };
        return eye;
    }
};

class CBaseAnimating : public CBaseEntity
{
public:

};

class CBasePlayer : public CBaseAnimating
{
public:
    NETVAR(get_life_state, "CBasePlayer", "m_lifeState", std::uint8_t);
    NETVAR(get_health, "CBasePlayer", "m_iHealth", std::int32_t);
    NETVAR(get_flags, "CBasePlayer", "m_fFlags", std::int32_t);
    NETVAR(get_tick_base, "CBasePlayer", "m_nTickBase", std::uint32_t);
    NETVAR(get_aim_punch, "CBasePlayer", "m_vecPunchAngle", vec3_t);
    NETVAR(get_view_offset, "CBasePlayer", "m_vecViewOffset[0]", vec3_t);
    NETVAR(get_next_attack, "CBaseCombatCharacter", "m_flNextAttack", float);
    ClientClass* GetClientClass()
    {
        typedef ClientClass* (__thiscall* get_clientclass_fn)(void*);
        return get_vfunc< get_clientclass_fn >(this, 2)(this);
    }

    bool IsDormant()
    {
        typedef bool(__thiscall* is_dormant_fn)(void*);
        return get_vfunc< is_dormant_fn >(this, 8)(this);
    }
   
};

class IClientNetworkable
{
public:

};

class CCSPlayer : public CBasePlayer
{
public:

};
