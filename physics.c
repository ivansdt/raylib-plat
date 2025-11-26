#include "raylib.h"





void updatePhysics(Player *player, Vector2 *velocity) {
    float gravity = 0.5f;
    if(player->isGrounded==false)
   {
      velocity->y +=gravity;
      }
    else
   {
    velocity->y +=0;
   }
}
 

