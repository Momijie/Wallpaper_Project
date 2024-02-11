
#include "engine.h"

#include "globals.h"
#include "unistd.h"

void SetCamera(Camera* camera, Vector3 position, Vector3 target, Vector3 up, float fovy) {
    camera->position   = position;
    camera->target     = target;
    camera->up         = up;
    camera->fovy       = fovy;
    camera->projection = CAMERA_PERSPECTIVE;
}

void SetOrnament(WW2_Ornament* ornament, const char* filename, int x, int y) {
    ornament->texture       = LoadTexture(filename);
    ornament->position.x    = (float)x;
    ornament->position.y    = (float)y;
    ornament->source.x      = 0;
    ornament->source.y      = 0;
    ornament->source.width  = ornament->texture.width;
    ornament->source.height = ornament->texture.height;
}

static void CheckArgs(lua_State* L, int check[]) {
    int n = lua_gettop(L);
    for (int i = 1; i <= n; i++) {
        luaL_checktype(L, i, check[i - 1]);
    }
}

static int fillArray(float array[], lua_State* L, int i) {
    if (!lua_istable(L, i)) {
        return luaL_error(L, "Not a table\n");
    }

    int it = 0;

    lua_pushnil(L);
    while (lua_next(L, i) != 0) {
        if (lua_type(L, -1) == LUA_TNUMBER) {
            array[it] = lua_tonumber(L, -1);
            it++;
        }
        lua_pop(L, 1);
        printf("\n");
    }
    return 0;
}

static int AddMascot(lua_State* L) {
    CheckArgs(L, ((int[]){LUA_TSTRING, LUA_TNUMBER, LUA_TNUMBER}));
    if (access(lua_tostring(L, 1), F_OK) != 0) {
        return luaL_error(L, "Can't access file at %s.\n", lua_tostring(L, 1));
    }

    SetOrnament(&ornament[0], lua_tostring(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));

    return 0;
}

static int AddCamera(lua_State* L) {
    CheckArgs(L, (int[]){LUA_TTABLE, LUA_TTABLE, LUA_TTABLE, LUA_TNUMBER});

    float position[3] = {0, 0, 0};
    float target[3]   = {0, 0, 0};
    float up[3]       = {0, 0, 0};
    float fovy        = 0;

    fillArray(position, L, 1);
    fillArray(target, L, 2);
    fillArray(up, L, 3);
    fovy = lua_tonumber(L, 4);

    printf("%f %f %f\n", position[0], position[1], position[2]);

    SetCamera(&camera,
              (Vector3){position[0], position[1], position[2]},
              (Vector3){target[0], target[1], target[2]},
              (Vector3){up[0], up[1], up[2]},
              fovy);

    return 0;
}

static int AddOrnament(lua_State* L) { return 0; }

luaL_Reg libs[] = {{"WW2API_add_camera", AddCamera},
                   {"WW2API_add_mascot", AddMascot},
                   {"WW2API_add_ornament", AddOrnament},
                   {NULL, NULL}};

void InitEngine(void) {
    lua_State* GL = luaL_newstate();
    luaL_openlibs(GL);
    lua_getglobal(GL, "_G");
    luaL_setfuncs(GL, libs, 0);
    luaL_dostring(GL, "print('LUA INFO: WAIFU WALLPAPER 2 LUA ENGINE UP AND RUNNING DESU!')");

    if (luaL_dofile(GL, LUA_INIT_FILE) != LUA_OK) {
        fprintf(stderr, "LUA ERROR: %s", lua_tostring(GL, -1));
    }
}
