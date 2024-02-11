#ifndef GLOBALS_H
#define GLOBALS_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "rlgl.h"
#include "x11func.h"

#define LUA_INIT_FILE "./lua/init.lua"
#define VERSION 1.0
#define ORNAMENT_MAX 1024

enum THEME { THEME_BACKGROUND = 0X1E1E2E };

typedef struct {
    int fps;
    int width;
    int height;
    char* title;
    Color backgroundColor;
} WW2_Window;

typedef struct {
    Texture texture;
    Rectangle source;
    Vector2 position;
} WW2_Ornament;

extern WW2_Ornament ornament[];
extern Camera camera;

extern void SetCamera(Camera* camera, Vector3 position, Vector3 target, Vector3 up, float fovy);
extern void SetOrnament(WW2_Ornament* ornament, const char* filename, int x, int y);

#endif
