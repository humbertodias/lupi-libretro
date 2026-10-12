#include "palette.h"

#include "ui.h"

#include <lauxlib.h>
#include <limits.h>
#include <stdio.h>

/*
 * lupi-codec packs BGR555 as bits 0-4 red, 5-9 green, 10-14 blue.
 * lupinho's palset still reads that word with red and blue swapped, so the
 * core provides the corrected entry point and renames the simulator copy
 * at compile time.
 */
extern Color palette[PALETTE_SIZE];

void palset(int position, int bgr555) {
    if (position < 0 || position >= PALETTE_SIZE) return;

    int r5 = (bgr555 >> 0) & 0x1F;
    int g5 = (bgr555 >> 5) & 0x1F;
    int b5 = (bgr555 >> 10) & 0x1F;

    palette[position].r = (unsigned char)((r5 << 3) | (r5 >> 2));
    palette[position].g = (unsigned char)((g5 << 3) | (g5 >> 2));
    palette[position].b = (unsigned char)((b5 << 3) | (b5 >> 2));
    palette[position].a = 255;
}

static char palette_game_dir[512];

static int lua_palette_hex(lua_State *L) {
    lua_Integer rgb = luaL_checkinteger(L, 1);
    int r = (int)((rgb >> 16) & 0xFF);
    int g = (int)((rgb >> 8) & 0xFF);
    int b = (int)(rgb & 0xFF);
    int want = ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3);

    lua_getglobal(L, "Palette");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_pushinteger(L, 0);
        return 1;
    }

    int best_i = 0;
    int best_dist = INT_MAX;
    int n = (int)luaL_len(L, -1);
    for (int i = 1; i <= n; i++) {
        lua_rawgeti(L, -1, i);
        int pal = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);

        if (pal == want) {
            lua_pop(L, 1);
            lua_pushinteger(L, i - 1);
            return 1;
        }

        int pr = pal & 0x1F;
        int pg = (pal >> 5) & 0x1F;
        int pb = (pal >> 10) & 0x1F;
        int dr = pr - (r >> 3);
        int dg = pg - (g >> 3);
        int db = pb - (b >> 3);
        int dist = dr * dr + dg * dg + db * db;
        if (dist < best_dist) {
            best_dist = dist;
            best_i = i - 1;
        }
    }

    lua_pop(L, 1);
    lua_pushinteger(L, best_i);
    return 1;
}

static int lua_palette_loader(lua_State *L) {
    char path[512];
    snprintf(path, sizeof(path), "%s/palette.lua", palette_game_dir);
    if (luaL_loadfile(L, path) != LUA_OK) {
        return lua_error(L);
    }
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        return lua_error(L);
    }

    lua_getglobal(L, "Palette");
    if (!lua_istable(L, -1)) {
        return luaL_error(L, "palette.lua did not define Palette table");
    }
    lua_pushcfunction(L, lua_palette_hex);
    lua_setfield(L, -2, "hex");
    return 1;
}

void lupi_install_palette_loader(lua_State *L, const char *game_dir) {
    snprintf(palette_game_dir, sizeof(palette_game_dir), "%s", game_dir);

    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, lua_palette_loader);
    lua_setfield(L, -2, "palette");
    lua_pop(L, 2);
}
