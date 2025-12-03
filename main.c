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
#include "math.h"
#include "animation.c"
#include "structures.c"
#include "physics.c"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera2D camera = {0};
Texture2D glubeIdle;
Texture2D glubeWalk;
Texture2D glubeJumpFall;

Rectangle sourceRec;

Texture2D currentAnim;
int currentAnimId;

BlendMode mult = BLEND_MULTIPLIED;
BlendMode add = BLEND_ADDITIVE;
static float delta;

Color CRIMSONSKY = {163, 39, 35, 255};
Color TRANSPARENTSKY = {163, 39, 35, 0};
Color SUNSET = {255, 194, 13, 170};
Color TRANSPARENTSUNSET = {255, 194, 13, 15};
Color HALFWHITE = {255, 255, 255, 64};

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

    camera.target = (Vector2){Player.position.x + 20.0f, Player.position.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Player.position.x = 200;
    Player.position.y = 200;
    Player.velocity.x = 0;
    Player.velocity.y = 0;

    glubeIdle = LoadTexture("resources/glube/glube_asset-sprite_idle_sheet.png");
    glubeWalk = LoadTexture("resources/glube/glube_asset-sprite_walk_sheet.png");
    glubeJumpFall = LoadTexture("resources/glube/glube_asset-sprite_jumpfall_sheet.png");

    initAnim(0, "GlobbIdle", 44.0f, 31.0f, 6);
    initAnim(1, "GlobbWalk", 65.0f, 32.0f, 8);
    initAnim(2, "GlobbJumpFall", 46.0f, 38.0f, 5);
    //--------------------------------------------------------------------------------------

#if defined(PLATFORM_WEB)

    emscripten_set_main_loop(DrawFrame, 60, 1);
#else
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ProccessInput();
        Update();
        DrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Input functions
void OnJumpKeyPressed()
{
    if (Player.isGrounded)
    {
        Player.velocity.y = -8;
        Player.isJumping = true;
    }
}

// Reset animation
void ResetAnim(int id)
{
    animations[id].current = 0;
    animations[id].frameCount = 0;
}

groundTile tiles[] = {
    {{50.0, 300.0}, {32.0, 32.0}}, // tile at (50 x,300 y), size 32x32
    {{150.0, 300.0}, {32.0, 48.0}},
    {{300.0, 300.0}, {64.0, 16.0}}};
int tileCount = sizeof(tiles) / sizeof(tiles[0]);

// Collision check
static void CheckTileCollisions(void)
{
    float playerWidth = 30;
    float playerHeight = 30;
    Rectangle playerRec = {Player.position.x, Player.position.y, playerWidth, playerHeight};

    for (int i = 0; i < tileCount; ++i)
    {
        Rectangle tileRec = {tiles[i].position.x, tiles[i].position.y, tiles[i].size.x, tiles[i].size.y};
        Player.collision = CheckCollisionRecs(playerRec, tileRec);
        if (Player.collision)
        {
            Player.velocity.y = 0;
            Player.isGrounded = true;
        }
    }
}

// Draw parallax rectangle
static void DrawRectanglePar(int posX, int posY, int sizeX, int sizeY, float offset, Color recColor)
{
    DrawRectangle((camera.target.x * offset) + posX, (camera.target.y * offset) + posY, sizeX, sizeY, recColor);
}

// Update
static void Update(void)
{
    delta = GetFrameTime();
    updatePhysics(delta);
    CheckTileCollisions();

    if (!Player.isGrounded)
    {
        if (Player.isJumping)
        {
            if (currentAnimId != 2)
            {
                ResetAnim(currentAnimId);
            }
            currentAnim = glubeJumpFall;
            currentAnimId = 2;
            sourceRec = animateJump(currentAnimId, 5);
            if (Player.direction < 0)
                sourceRec.width = sourceRec.width * -1;
            else
                sourceRec.width = sqrt(sourceRec.width * sourceRec.width);
        }
        else
        {
            if (currentAnimId != 2)
            {
                ResetAnim(currentAnimId);
            }
            currentAnim = glubeJumpFall;
            currentAnimId = 2;
            if (animations[currentAnimId].current == 0)
                animations[currentAnimId].current = 3;
            sourceRec = animateJump(currentAnimId, 5);
            if (Player.direction < 0)
                sourceRec.width = sourceRec.width * -1;
            else
                sourceRec.width = sqrt(sourceRec.width * sourceRec.width);
        }
    }
    else if (!Player.isMoving && Player.isGrounded)
    {
        if (currentAnimId != 0)
        {
            ResetAnim(currentAnimId);
        }
        currentAnim = glubeIdle;
        currentAnimId = 0;
        sourceRec = animate(currentAnimId, 6);
        if (Player.direction < 0)
            sourceRec.width = sourceRec.width * -1;
        else
            sourceRec.width = sqrt(sourceRec.width * sourceRec.width);
    }
    else if (Player.isGrounded)
    {
        if (currentAnimId != 1)
        {
            ResetAnim(currentAnimId);
        }
        currentAnim = glubeWalk;
        currentAnimId = 1;
        sourceRec = animate(currentAnimId, 8);
        currentAnim = glubeWalk;
        if (Player.direction < 0)
            sourceRec.width = sourceRec.width * -1;
        else
            sourceRec.width = sqrt(sourceRec.width * sourceRec.width);
    }
}
// Proccess inputs
static void ProccessInput(void)
{
    Player.isMoving = false;

    if (IsKeyDown(KEY_A))
    {
        Player.position.x -= Player.velocity.x + 3;
        Player.isMoving = true;
        Player.direction = 1;
    }

    if (IsKeyDown(KEY_D))
    {
        Player.position.x += Player.velocity.x + 3;
        Player.isMoving = true;
        Player.direction = -1;
    }

    if (IsKeyPressed(KEY_SPACE))
        OnJumpKeyPressed();
}

// Draw frame
static void DrawFrame(void)
{
    // Draw
    //----------------------------------------------------------------------------------

    ClearBackground(RAYWHITE);
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenWidth(), GetColor(0xA32723ff), GetColor(0xFFC405ff));

    BeginMode2D(camera);

    camera.target.x = Player.position.x + 20.0f;
    camera.target.y = Player.position.y - 30.0f;

    // Mountains
    DrawRectanglePar(-500, 50, 2000, 800, 0.5f, GetColor(0x1B2414ff));

    // Mid buildings
    DrawRectanglePar(-250, 0, 200, 600, 0.3f, GetColor(0x543A2Cff));
    DrawRectanglePar(180, -300, 120, 900, 0.3f, GetColor(0x543A2Cff));
    DrawRectanglePar(540, -200, 220, 800, 0.3f, GetColor(0x543A2Cff));

    // Mid ground
    DrawRectanglePar(-500, 320, 1500, 700, 0.3f, GetColor(0x2B3D12ff));

    // Front buildings
    DrawRectanglePar(0, -100, 200, 700, 0.1f, GetColor(0x825A44ff));
    DrawRectanglePar(400, -400, 210, 1000, 0.1f, GetColor(0x825A44ff));
    DrawRectanglePar(750, -250, 170, 850, 0.1f, GetColor(0x825A44ff));

    DrawRectangle(-500, 431, 1500, 600, GetColor(0x44611Dff));

    // Draw ground tiles (in world coordinates) first so the player is drawn on top
    for (int i = 0; i < tileCount; ++i)
    {
        DrawRectangleV(tiles[i].position, tiles[i].size, GetColor(0x0F0904ff));
    }

    // Draw player using world position
    DrawTextureRec(currentAnim, sourceRec, (Vector2){Player.position.x, Player.position.y}, WHITE);

    EndMode2D();

    // Blend
    BeginBlendMode(mult);
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenWidth(), CRIMSONSKY, TRANSPARENTSUNSET);
    EndBlendMode();

    // Blend
    BeginBlendMode(add);
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenWidth(), TRANSPARENTSKY, SUNSET);
    EndBlendMode();

    DrawFPS(GetScreenWidth() - 80, 10);

    DrawText(TextFormat("Current anim: %s", animations[currentAnimId].name), 10, 10, 20, HALFWHITE);
    DrawText(TextFormat("Anim frame: %i/%i (x: %.2f)", animations[currentAnimId].current + 1, animations[currentAnimId].fps, sourceRec.x), 10, 30, 20, HALFWHITE);
    DrawText(TextFormat("Y Speed: %.2f", Player.velocity.y), 10, 50, 20, HALFWHITE);
    DrawText(TextFormat("Y Pos: %.2f", Player.position.y), 10, 70, 20, HALFWHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
