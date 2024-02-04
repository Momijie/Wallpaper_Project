#include "raylib.h"
#include "x11func.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

struct Window {
    int fps;
    int width;
    int height;
    char title[30];
};

struct Mascot {
    Texture2D texture;
    Vector2 position;
};

struct Ornament {
    Texture2D texture;
    Vector2 position;
};

int main(void)
{
   struct Window window;
   window.fps = 60;
   window.width = 100;
   window.height = 100;
   strncpy(window.title, "dog", sizeof(window.title));
   

    InitWindow(window.width, window.height, window.title);
    InitGame();
    GetProgramWindow();
    SetTargetFPS(window.fps);
    
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    UnloadGame();
    CloseWindow();

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------
void InitGame(void)
{
}

// Update game (one frame)
void UpdateGame(void)
{
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(RAYWHITE);

    EndDrawing();
}

void UnloadGame(void)
{
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

