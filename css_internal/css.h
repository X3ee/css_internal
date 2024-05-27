#pragma once

#include "sdk.h"
typedef void* (*CreateInterfaceFn)(const char*, int*);
typedef void(__thiscall* paint_fn)(void*, PaintMode_t);
#include "d3dx9.h"
extern paint_fn				o_paint;

struct css {

public:
    IBaseClientDll* m_client;
    IPanel* m_panel;
    IVEngineClient* m_engine;
    ISurface* m_surface;
    ICvar* m_cvar;
    IClientEntityList* m_entitylist;
    IDirect3DDevice9* d3d_device;
    CInput* m_input;
    ClientMode* m_client_mode;
    bool update();

    void initialize();

    void dispose();
    // Stuff
    void init_interfaces();
};
extern css g_css;