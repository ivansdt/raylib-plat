/*******************************************************************************************
 *
 *   raylib [core] example - Basic 3d example
 *
 *   Welcome to raylib!
 *
 *   To compile example, just press F5.
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include "animation.c"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera2D camera = {0};
Texture2D glubeIdle;
Rectangle sourceRec;
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ProccessInput(void);
static void Update(void);
static void DrawFrame(void); // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    glubeIdle = LoadTexture("resources/glube/glube_asset-sprite_idle_sheet.png");

    init_GlubeIdle();
    //--------------------------------------------------------------------------------------

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(DrawFrame, 60, 1);
#else
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Update();
        ProccessInput();
        DrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update
static void Update(void)
{
    sourceRec = animate_GlubeIdle();
}
// Proccess inputs
static void ProccessInput(void)
{
}
// Draw frame
static void DrawFrame(void)
{
    // Draw
    //----------------------------------------------------------------------------------
    BeginMode2D(camera);

    ClearBackground(RAYWHITE);
    DrawTextureRec(glubeIdle, sourceRec, (Vector2){200, 300}, WHITE);

    DrawText(TextFormat("Current frame: %i", animations[0].current), 10, 35, 20, RED);
    DrawText(TextFormat("SourceRec.x: %f", sourceRec.x), 10, 55, 20, RED);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
