#pragma once
#include "framework.h"
#include "css.h"
struct ctx
{
public:

	bool m_unload;
	bool* m_send_packet;
	CCSPlayer* local();

};
extern ctx g_ctx;