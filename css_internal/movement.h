#include "sdk.h"
struct movement {
public:
	void handle(CUserCmd* cmd);
private:
	void faststop(CUserCmd* cmd);
	void bhop(CUserCmd* cmd);
};