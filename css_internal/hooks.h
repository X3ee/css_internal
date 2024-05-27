#pragma once
#include "sdk.h"
#include "css.h"

struct hooks {
public:
	void init();
	void unhook();
private:
	inline unsigned int get_virtual(void* _class, unsigned int index) {
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]);
	}
};

extern hooks g_hooks;