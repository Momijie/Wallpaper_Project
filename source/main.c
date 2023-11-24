#include "raylib.h"
#include "x11func.h"
#include <stdint.h>
#include <stdio.h>

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
int main(void)
{
    const int fps = 60;
    const int width = 1920/2;
    const int height = 1080/2;


    InitWindow(width,height, "ww2");
    InitGame();

    GetProgramWindow(GetWindowHandle());


    SetTargetFPS(fps);
    
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

