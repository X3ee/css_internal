#include "sdk.h"



uintptr_t util::find_pattern(const char* szModule, const char* szSignature)
{
	MODULEINFO modInfo;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
	uintptr_t startAddress = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
	uintptr_t endAddress = startAddress + modInfo.SizeOfImage;
	const char* pat = szSignature;
	uintptr_t firstMatch = 0;
	for (uintptr_t pCur = startAddress; pCur < endAddress; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else
		{
			pat = szSignature;
			firstMatch = 0;
		}
	}

	return NULL;
}

DWORD_PTR util::getmodulebase(const char* name)
{
	HMODULE m = GetModuleHandleA(name);

	if (m == 0)
		return 0;

	MODULEINFO module_info;
	GetModuleInformation(GetCurrentProcess(), m, &module_info, sizeof(module_info));

	return (DWORD_PTR)module_info.lpBaseOfDll;
}


int util::floatrgba(float value)
{
	return value * 255;
}

std::uintptr_t util::get_rel32(std::uintptr_t address, std::uintptr_t offset, std::uintptr_t instruction_size)
{
	return address + *reinterpret_cast<std::uintptr_t*>(address + offset) + instruction_size;
}

bool util::IsCodePtr(void* ptr)
{
	constexpr const DWORD protect_flags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

	MEMORY_BASIC_INFORMATION out;
	VirtualQuery(ptr, &out, sizeof out);

	return out.Type
		&& !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS))
		&& out.Protect & protect_flags;
}