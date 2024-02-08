#include "engine.h"

#include <lauxlib.h>
#include <lua.h>
#include <luaconf.h>
#include <stdio.h>

#include "globals.h"
#include "unistd.h"

lua_State* GL;

void SetOrnament(struct Ornament* ornament, const char* filename, int x, int y) {
    ornament->texture       = LoadTexture(filename);
    ornament->position.x    = (float)x;
    ornament->position.y    = (float)y;
    ornament->source.x      = 0;
    ornament->source.y      = 0;
    ornament->source.width  = ornament->texture.width;
    ornament->source.height = ornament->texture.height;
}

static int AddMascot(lua_State* L) {
    int n       = lua_gettop(L);
    int check[] = {LUA_TSTRING, LUA_TNUMBER, LUA_TNUMBER};

    for (int i = 1; i <= n; i++) {
        luaL_checktype(L, i, check[i - 1]);
    }

    if (access(lua_tostring(L, 1), F_OK) != 0) {
        return luaL_error(L, "Can't access file at %s.\n", lua_tostring(L, 1));
    }

    SetOrnament(&ornament[0], lua_tostring(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));

    return 0;
}

static int AddOrnament(lua_State* L) { return 0; }

luaL_Reg libs[] = {{"WW2API_add_mascot", AddMascot}, {"WW2API_add_ornament", AddOrnament}, {NULL, NULL}};

void InitEngine(void) {
    GL = luaL_newstate();
    luaL_openlibs(GL);
    lua_getglobal(GL, "_G");
    luaL_setfuncs(GL, libs, 0);
    luaL_dostring(GL, "print('LUA INFO: WAIFU WALLPAPER 2 LUA ENGINE UP AND RUNNING DESU!')");

    if (luaL_dofile(GL, LUA_INIT_FILE) != LUA_OK) {
        fprintf(stderr, "LUA ERROR: %s", lua_tostring(GL, -1));
    }
}
