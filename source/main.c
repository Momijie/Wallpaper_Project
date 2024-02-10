#include <lauxlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"
#include "globals.h"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
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
Camera camera = {0};
Texture2D texture;
Model sphere;
int main(void) {
    SetWindow(&window, "Wallpaper Waifu2", 60, 1920, 1080);
    InitWindow(window.width, window.height, window.title);
    InitGame();
    InitEngine();

    texture = LoadTexture("/home/satori/Development/Wallpaper_Project/build/res/curved4.png");
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture");
    }
    sphere                                                 = LoadModelFromMesh(GenMeshSphere(1.0f, 32, 32));
    sphere.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

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
float rotation = 0.0f;
void InitGame(void) { FlipOrnament(&ornament[0]); }

void UpdateGame(void) {}
void DrawGame(void) {
    BeginDrawing();
    ClearBackground(window.backgroundColor);
    BeginMode3D(camera);
    rotation += 1;
    DrawModelEx(
        sphere, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, rotation, (Vector3){1.0f, 1.0f, 1.0f}, WHITE);
    EndMode3D();
    DrawTextureRec(ornament[0].texture, ornament[0].source, ornament[0].position, WHITE);
    EndDrawing();
}

void UnloadGame(void) {}

void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}
