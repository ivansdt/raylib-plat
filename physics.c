#include "raylib.h"

static int gravity = 2;
static int ground = 400;
int goopMeter = 60;
Color GOOPGREEN = {0, 255, 0, 0};

void updatePhysics(float time)
{
    Player.position.y += Player.velocity.y;

    Player.velocity.y += gravity * (time * 6);

    if (Player.position.y >= ground)
    {
        if (Player.isJumping)
        {
            Player.isJumping = false;
        }
        else
        {
            Player.isGrounded = true;
            Player.velocity.y = 0;
            Player.position.y = ground;
        }
    }

    if (Player.position.y < ground)
    {
        Player.isGrounded = false;
    }

    if (goopMeter < 1)
    {
        Player.isGooping = false;
    }
    if (Player.isGooping)
    {
        if (GOOPGREEN.a < 255)
            GOOPGREEN.a += 51;
        else
            GOOPGREEN.a = 255;
        goopMeter--;
        if (goopMeter > 0)
        {
            Player.velocity.y = 0;
            Player.velocity.x = 0;
        }
    }
}

groundTile tiles[] = {
    {{50.0, 300.0}, {32.0, 32.0}}, // tile at (50 x,300 y), size 32x32
    {{150.0, 340.0}, {32.0, 48.0}},
    {{400.0, 350.0}, {64.0, 16.0}},
    {{300.0, 50.0}, {100.0, 250.0}}};
int tileCount = sizeof(tiles) / sizeof(tiles[0]);

// Collision check
static void CheckTileCollisions(void)
{
    float playerWidth = 42;
    float playerHeight = 32;
    Rectangle playerRec = {Player.position.x, Player.position.y, playerWidth, playerHeight};
    Player.hitWallL = false;
    Player.hitWallR = false;

    for (int i = 0; i < tileCount; ++i)
    {
        Rectangle tileRec = {tiles[i].position.x, tiles[i].position.y, tiles[i].size.x, tiles[i].size.y};
        Player.collision = CheckCollisionRecs(playerRec, tileRec);
        if (Player.collision && Player.position.y + 23 - Player.velocity.y <= tiles[i].position.y && !Player.isGooping && Player.velocity.y >= 0)
        {
            Player.velocity.y = 0;
            Player.isGrounded = true;
            Player.isJumping = false;
            Player.position.y = tiles[i].position.y - 30 - Player.velocity.y;
            Player.isGooping = false;
        }
        else if (Player.collision && playerRec.x <= tiles[i].position.x - 30)
        {
            Player.velocity.x = -4;
            Player.hitWallR = true;
        }
        else if (Player.collision && playerRec.x >= tiles[i].position.x + (tiles[i].size.x * 7 / 8))
        {
            Player.velocity.x = 4;
            Player.hitWallL = true;
        }
        else if (Player.collision && Player.position.y >= tiles[i].position.y)
        {
            Player.velocity.y = 1;
        }
    }
}