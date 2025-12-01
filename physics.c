#include "raylib.h"

void updatePhysics(Entity Player, Vector2 velocity)
{
    
    if (Player.position.y == 200)
    {
        Player.isGrounded = true;
        velocity.y = 0;
    }
    else if (Player.position.y < 200)
    {
        Player.isGrounded = false;
    }

    float gravity = 1.0f;
    if (!Player.isGrounded == false)
    {
        velocity.y += gravity;
    }
}
