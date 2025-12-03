#include "raylib.h"

typedef struct {
    Vector2 position;
    int direction;
    float maxSpd;
    float acc;
    float dcc;
    float gravity;
    float jumpImpulse;
    float jumpRelease;
    Vector2 velocity;
    // Carry stored subpixel values
    float hsp;
    float vsp;
    int keyPressed;

    bool isGrounded;
    bool isJumping;
    bool isMoving;
    // Flags for detecting collision
    bool collision;
    bool hitWall;

} Entity;

static Entity Player = { 0 };

typedef struct  {
    Vector2 position;
    Vector2 size;

} groundTile;

