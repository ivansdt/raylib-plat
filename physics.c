#include "raylib.h"

static int gravity = 2;
static int ground = 400;



void updatePhysics(float time)
{

    Player.position.y += Player.velocity.y;
    Player.velocity.y += gravity * time;

    if (Player.position.y >= ground)
    {
        Player.isGrounded = true;
        Player.velocity.y = 0;
    }

    if (Player.position.y < ground)
    {
        Player.isGrounded = false;
    }


}
