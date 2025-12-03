#include "raylib.h"

static int gravity = 2;
static int ground = 400;



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
}

groundTile tiles[] = {
    { {  50.0, 300.0 }, { 32.0, 32.0 } },   // tile at (50 x,300 y), size 32x32
    { { 150.0, 340.0 }, { 32.0, 48.0 } },  
    { { 300.0, 350.0 }, { 64.0, 16.0 } }    
};
int tileCount = sizeof(tiles) / sizeof(tiles[0]);

// Collision check
static void CheckTileCollisions(void)
{
    float playerWidth = 40;
    float playerHeight = 32;
    Rectangle playerRec = { Player.position.x, Player.position.y, playerWidth, playerHeight };
    
    for (int i = 0; i < tileCount; ++i) {
        Rectangle tileRec = { tiles[i].position.x, tiles[i].position.y, tiles[i].size.x, tiles[i].size.y };
       Player.collision = CheckCollisionRecs(playerRec, tileRec);
        if (Player.collision && Player.position.y + 23 - Player.velocity.y <= tiles[i].position.y)  {
            Player.velocity.y = 0;
            Player.isGrounded = true;
            Player.isJumping = false;
        }
        else if (Player.collision && playerRec.x <= tileRec.x )
        {
            Player.velocity.x = -1;
        }
        else if (Player.collision && Player.position.y >= tiles[i].position.y )
        {
            Player.velocity.y = 1;
        }
    }
}