#include "sdk.h"


struct movement {
public:
	CUserCmd* m_ucmd{ };
	void handle(CUserCmd* cmd);
	void bhop();
	void jumpikiii();
private:
	void faststop(CUserCmd* cmd);
	

};
extern movement g_movement;