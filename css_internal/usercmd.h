#pragma once

enum PlayerStates_t
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8),
	FL_INWATER = (1 << 9),
};

enum PlayerControls_t
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON1 = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_GRENADE1 = (1 << 23),
	IN_GRENADE2 = (1 << 24),
	IN_ATTACK3 = (1 << 25),
};



struct CUserCmd
{
    int     commandNumber;              // The command number (good for keeping track of ticks)
    int     tickCount;                  // Tick count (change for backtrack)
    std::vector<int>  viewangles;       // viewAngles (i think u know what happens here)
    //std::vector<int>  aimdirection;   // Outdated/irrelivant/don't touch it
    float   forwardmove,
        sidemove,
        upmove;                     // Moving in directions (450 to -450)
    int     buttons;                    // Button flags (IN_ATTACK, IN_DUCK, etc.)
    char    impulse;
    int     weaponselect,
        weaponsubtype;              // Held weapon slot (1 - 6) and sub-selection
    int     randomSeed;                 // Outdated (used to give the server seed but now is just 0 24/7)
    short   mousedx,
        mousedy;                    // uselss unless ur tryna bypass facit anticheatmousedy;
    bool    hasbeenpredicted;           // don't mess with this its useful for certain prediction things
};