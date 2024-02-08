#ifndef GLOBALS_H
#define GLOBALS_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "raylib.h"

#define LUA_INIT_FILE "./lua/init.lua"
#define VERSION 1.0
#define ORNAMENT_MAX 1024

enum THEME {
    THEME_BACKGROUND = 0X1E1E2E

};

struct Window {
    int fps;
    int width;
    int height;
    char* title;
    Color backgroundColor;
};

struct Ornament {
    Texture2D texture;
    Rectangle source;
    Vector2 position;
};

extern struct Ornament ornament[];

extern lua_State* GL;
#endif
