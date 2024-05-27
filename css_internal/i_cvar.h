#pragma once

#include "util.h"
#include "color.h"

struct ICvar
{
	// Prints to console (colors)
	template <typename... Values>
	void ConsoleColorPrintf(const Color& msgcolor, const char* format, Values... parameters)
	{
		GetVFunction <void(__cdecl*)(ICvar*, const Color&, const char*, ...)>(this, 23)(this, msgcolor, format, parameters...);
	}
	virtual ICvar* FindVar(const char* var_name) = 0;
	virtual const ICvar* FindVar(const char* var_name) const = 0;

	float GetFloat() {
		using fn = float(__thiscall*)(void*);
		return GetVFunction< fn >(this, 12)(this);
	}

	// Prints to console
	template <typename... Values>
	void ConsoleDPrintf(const char* format, Values... parameters)
	{
		GetVFunction<void(__cdecl*)(ICvar*, const char*, ...)>(this, 24)(this, format, parameters...);
	}

};

