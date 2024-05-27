#pragma once

#include "sdk.h"
typedef void* (*CreateInterfaceFn)(const char*, int*);



struct css {


public:
    
    IBaseClientDll* m_client;
    IPanel* m_panel;
    IVEngineClient* m_engine;
    ISurface* m_surface;
    ICvar* m_cvar;
    IClientEntityList* m_entitylist;
  

    bool update();

    void initialize();

    void dispose();

    // Stuff
    void init_interfaces();
 
};
extern css g_css;