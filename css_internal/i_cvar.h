#pragma once

#include "util.h"
#include "color.h"

struct ICvar
{
	ICvar* cvar;
	/*
	_BYTE *__thiscall sub_10247920(
        _BYTE *this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        float a7,
        int a8,
        float a9,
        int a10)
{
  this[8] = 0;
  *((_DWORD *)this + 3) = 0;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 6) = &IConVar::`vftable';
  *(_DWORD *)this = &ConVar::`vftable';
  *((_DWORD *)this + 6) = &ConVar::`vftable';
  sub_10248210(a2, a3, a4, a5, a6, LODWORD(a7), a8, LODWORD(a9), a10);
  return this;
}
	*/
	struct value_t
	{
		char* m_pszString;
		int		m_StringLength;
		float	m_fvalue;
		int		m_nvalue;
	};
	value_t				m_value;
	// Prints to console (colors)
	template <typename... Values>
	void ConsoleColorPrintf(const Color& msgcolor, const char* format, Values... parameters)
	{
		GetVFunction <void(__cdecl*)(ICvar*, const Color&, const char*, ...)>(this, 23)(this, msgcolor, format, parameters...);
	}
	virtual ICvar* FindVar(const char* var_name) = 0;
	virtual const ICvar* FindVar(const char* var_name) const = 0;

	/*float GetFloat() {
		using fn = float(__thiscall*)(void*);
		return GetVFunction< fn >(this, 12)(this);
	}*/

	float GetFloat(void) const
	{
		return cvar->m_value.m_fvalue;
	}

	// Prints to console
	template <typename... Values>
	void ConsoleDPrintf(const char* format, Values... parameters)
	{
		GetVFunction<void(__cdecl*)(ICvar*, const char*, ...)>(this, 24)(this, format, parameters...);
	}

};

