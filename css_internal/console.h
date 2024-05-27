#pragma once
#include "framework.h"

struct console {
public:
	void main(const char* title);
	void undo();

	template <typename ... Args>
	void log(char const* const format, Args const& ... args) {

		printf(format, args ...);

	}
};
extern console g_con;