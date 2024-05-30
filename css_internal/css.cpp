#include "css.h"
#include "framework.h"
#include "console.h"
#include "hooks.h"

void css::initialize() {
 
  g_con.main("cash hack");
  g_con.log("base adress 0x%p\n"), (void*)util::getmodulebase("hl2.exe");
  g_con.log("\ninterfaces no bitches\n");
}

void css::destroy() {
    g_con.log("unhooked\n\n");
    g_hooks.unhook();
    g_con.undo();
}

bool css::update() {
    return true;
}
