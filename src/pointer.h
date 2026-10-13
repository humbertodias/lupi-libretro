#ifndef LUPI_POINTER_H
#define LUPI_POINTER_H

#include "libretro.h"
#include <lua.h>

void lupi_pointer_poll(retro_input_state_t cb);
void lupi_pointer_install(lua_State *L);

#endif
