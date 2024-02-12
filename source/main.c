
#include <raylib.h>

#include "engine.h"
#include "globals.h"

static void InitGame(void);
static void UpdateGame(void);
static void DrawMascot(void);
static void Draw3DGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);
static void SetWindow(WW2_Window* window, char* title, int fps, int width, int height);

WW2_Ornament ornament[ORNAMENT_MAX];
WW2_Window window;
Camera camera = {0};

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

static void InitGame(void) {}
static void UpdateGame(void) {}
static void DrawMascot(void) { DrawTextureRec(ornament[0].texture, ornament[0].source, ornament[0].position, WHITE); }
static void Draw3DGame(void) {
    BeginMode3D(camera);
    EndMode3D();
}
static void DrawGame(void) {
    BeginDrawing();
    ClearBackground(window.backgroundColor);
    DrawMascot();
    EndDrawing();
}
static void UnloadGame(void) {}
static void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}

static void SetWindow(WW2_Window* window, char* title, int fps, int width, int height) {
    window->fps             = fps;
    window->width           = width;
    window->height          = height;
    window->title           = title;
    window->backgroundColor = GetColor(THEME_BACKGROUND);
}

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
