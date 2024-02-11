
#include "engine.h"
#include "globals.h"

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);
static void SetWindow(WW2_Window* window, char* title, int fps, int width, int height);

WW2_Ornament ornament[ORNAMENT_MAX];
WW2_Window window;
Camera camera = {0};
Texture2D texture;
Model sphere;
// temporary
float rotation = 0.0f;

int main(void) {
    SetWindow(&window, "Wallpaper Waifu2", 60, 1920, 1080);
    InitWindow(window.width, window.height, window.title);
    InitGame();
    InitEngine();

    texture = LoadTexture("./res/checker.png");
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture");
    }
    sphere                                                 = LoadModelFromMesh(GenMeshSphere(2.0f, 64, 64));
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

void InitGame(void) {}

void UpdateGame(void) {}
void DrawGame(void) {
    BeginDrawing();
    ClearBackground(window.backgroundColor);
    BeginMode3D(camera);
    rotation += 1;
    DrawModelEx(
        sphere, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){1.0f, 1.0f, 0.0f}, rotation, (Vector3){4.0f, 4.0f, 4.0f}, WHITE);
    EndMode3D();
    DrawTextureRec(ornament[0].texture, ornament[0].source, ornament[0].position, WHITE);
    EndDrawing();
}

void UnloadGame(void) {}

void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}

void SetWindow(WW2_Window* window, char* title, int fps, int width, int height) {
    window->fps             = fps;
    window->width           = width;
    window->height          = height;
    window->title           = title;
    window->backgroundColor = GetColor(THEME_BACKGROUND);
}
