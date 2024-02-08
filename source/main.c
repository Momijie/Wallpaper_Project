#include <lauxlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "globals.h"
#include "raylib.h"
#include "x11func.h"

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

void SetWindow(struct Window* window, char* title, int fps, int width, int height) {
    window->fps             = fps;
    window->width           = width;
    window->height          = height;
    window->title           = title;
    window->backgroundColor = GetColor(THEME_BACKGROUND);
}
struct Ornament ornament[ORNAMENT_MAX];
struct Window window;
Texture2D texture;

int main(void) {
    SetWindow(&window, "Wallpaper Waifu2", 60, 1920, 1080);
    InitWindow(window.width, window.height, window.title);
    InitGame();
    InitEngine();
    GetProgramWindow();
    SetTargetFPS(window.fps);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
    UnloadGame();
    CloseWindow();
    return 0;
}

void FlipOrnament(struct Ornament* ornament) { ornament->source.width = -ornament->texture.width; }

void InitGame(void) { FlipOrnament(&ornament[0]); }

void UpdateGame(void) {}

void DrawGame(void) {
    BeginDrawing();
    ClearBackground(window.backgroundColor);
    DrawTextureRec(ornament[0].texture, ornament[0].source, ornament[0].position, WHITE);
    EndDrawing();
}

void UnloadGame(void) {}

void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}
