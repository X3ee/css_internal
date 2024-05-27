#pragma once
#include "framework.h"
#include "css.h"
struct local
{
public:

	bool m_unload;
	bool* m_send_packet;
	CCSPlayer* getlocalplayer();

};
extern local localplayer;